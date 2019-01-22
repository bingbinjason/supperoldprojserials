//------------------------------------桌球-----------------------------------//

#include "core.h"
int news=0,dels=0,fals=0;
static float tmstep=0.08f;
#include <vector>

enum GAMESTA{GST_XUMU,GST_MENU,GST_READY,GST_PAUSE,GST_GAMING,GST_GAMEEND,GST_CONTINUE};
enum GAMETYP{GTP_AM9,GTP_SNK,GTP_LUODAI8,};
enum EFTTYP{EFT_NONE,EFT_TIPBALL,EFT_WIN,EFT_LOSE,EFT_SCR};

#define GAMEFPOT Point3(0,0,0) //初始相机位置
#define GAMETABLP Point3(0,0,0) //初始球桌位置
#define BALLP	Point3(0,0,0)//球位置
#define TABLS 1				//球桌缩放比例
#define TABLWH 	0.4f		//球桌长宽比
#define TABLL	20.0f		//桌厚
#define TABLW	400			//球桌长
#define BALLR	4.0f		//球大小
#define BALLM	2.5f		//球质量
#define BALLF	0.5f		//球摩擦系数  
#define TABLF	0.4f		//球桌摩擦系数
#define TICKR	1.0f		//球棒前端半径
#define TICKH	120.0f		//棒长

int ball_clrtbl[17]={8,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7};//颜色表
int ball_snkclrtb[8]={8,2,0,5,6,1,4,7,};//斯诺克颜色表

int ball_us9tbl[10]={0,2,7,3,6,9,8,1,5,4};//US9排列表
int ball_ld8tbl[17]={0,3,12,4,14,5,10,11,13,15,2,8,6,7,9,1};//落袋16球排列表


inline void clampv(Vector3 &v,float n)
{
	float l=v.Mod();
	if(l>n)l=n;
	v.Unit();
	v=v*l;
}
INT64 lpFrequency,ticks_per_ms;
void inittimer()
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&lpFrequency);
	ticks_per_ms = lpFrequency/10000;
}
inline INT64 gettimer(void)
{
	INT64 lpPerformanceCount;
	QueryPerformanceCounter((LARGE_INTEGER *)&lpPerformanceCount);
	return lpPerformanceCount;
}

class _gdata
{
public:
	GAMESTA gamesta,oldsta;
	GAMETYP gametyp;
	char gameplayers;
	int currplayer;
	int mousebar;
	float e,friction,timstep,bcheckstickcollid,impulls,fps,mouserev;
	void *zuoqiu;
public:
	_gdata(void * zq=NULL)
	{
		zuoqiu=zq;
		init();
	};
	void init()
	{
		currplayer=0;
		gameplayers=0;
		gamesta=GST_XUMU;
		oldsta=GST_XUMU;
		gametyp=GTP_AM9;
		mousebar=0;
		e=0.8f;
		friction=0.7f;
		timstep=0.04f;
		fps=160;
		impulls=1.5f;
		bcheckstickcollid=0;
		mouserev=1;
	};
};

struct Eftstr
{
	EFTTYP Eftp;
	Point3 pos;
	unsigned int dtime,lagtime;
	bool flg,enable;
	int scr;
	Point2 ps[4];
	
	Eftstr()
	{
		init();
	}
	void init()
	{
		Eftp=EFT_NONE;
		dtime=lagtime=0;
		enable=true;
		flg=false;
	}
};
class _ball:public Body
{
public:
	_gdata *gdt;
	int c, scr,id,idx;
	int bc;//彩球/单色球
	bool bjind;//进洞
	bool bout;
	float v;//速度
public:
	void SetGdt(_gdata *g=NULL){gdt=g;}
	_ball()
	{
		gdt=NULL;
		v=0;
		bjind=false;
		bout=false;
		bc=-1;//-1为非snk用球
		c=30;
		scr=0;
		idx=0;
		SetSphere(BALLR,BALLM);
	};
	void clearmove()
	{
		_vel=Vector3(0,0,0);
		_angvel=Vector3(0,0,0);
		_quat.Unit();
	};
	void reset();
	void calc();
	void SetID(int tid, int ix=0)
	{
		if(tid<0||tid>15)return;
		c=ball_clrtbl[tid]*7+1;
		scr=tid;	id=tid; idx=ix;
	}
	void SetSnkID(int tid, int ix=0)
	{
		if(tid<0||tid>21)return;
		c=ball_snkclrtb[tid]*7+1;
		scr=tid;	id=tid; idx=ix;
		if(id>0&&id<16)bc=0;
		else if(id>15&& id<22)bc=1;
	}
	void DrawCir(int cr=57,bool f=false)
	{
		Vector3 axs[3];
		axs[0]=RDev.SysCamera->_v;
		axs[1]=RDev.SysCamera->_n;
		axs[2]=RDev.SysCamera->_u;
		DrawCircle(_pos,axs,BALLR,cr);
		if(f)
		{
			FillCircle(_pos,axs,BALLR,cr);
		}
	};
	void DrawShadow()
	{
		Vector3 axs[3];
		CreateAxis(axs);
		Vector3 sps=_pos;
		float shr=BALLR;
		if( sps.y>-BALLR-0.2f)return;
		sps.y=0;
		DrawCircle(sps,axs,BALLR-0.2,59);
	};
	void DrawTipprim()
	{
		Vector3 axs[3];
		Quat qt=Quat(Vector3(0,1,0),(GetTickCount()/50)*Pi);
		axs[0]=Vector3(1,0,0)*qt;
		axs[1]=Vector3(0,1,0);
		axs[2]=Vector3(0,0,1)*qt;
		Vector3 tp[5],sp;
		float ww=1;
		sp=_pos+Vector3(0,(GetTickCount()/200)%3-3*BALLR,0);
		tp[0]=axs[0]*-ww+ axs[2]*ww+sp;
		tp[1]=axs[0]*ww+axs[2]*ww+sp;
		tp[2]=axs[0]*ww+axs[2]*-ww+sp;
		tp[3]=axs[0]*-ww+axs[2]*-ww+sp;
		tp[4]=axs[1]*3+sp;
		line3(tp[0],tp[1],57);
		line3(tp[1],tp[2],57);
		line3(tp[2],tp[3],57);
		line3(tp[3],tp[0],57);

		line3(tp[0],tp[4],57);
		line3(tp[1],tp[4],57);
		line3(tp[2],tp[4],57);
		line3(tp[3],tp[4],57);
	}
	void DrawBall(bool sp=false)
	{
		if(bjind)return;
		if(!RDev.SysCamera->SPHBInFrustum(SphereT(_pos,rad)))return;
		if(sp)
		{
			DrawCir(c);
			return;
		}
		DrawShadow();
		DrawCir(0,true);
	
		if(getkey(VK_SPACE))
		{	
			DrawCir(c);
			Vector3 rz=Rasterize(_pos);
			print_num(rz.x-2,rz.y-2,id,57);
			return;
		}
#define NUM_SEG 10
		Vector3 ax[3];
		ax[0]=_Axis[0]*_quat;
		ax[1]=_Axis[1]*_quat;
		ax[2]=_Axis[2]*_quat;

		Point3 p,p1,np1;
		double w,u,k;
		Vector3 vt[NUM_SEG+1],nvt[NUM_SEG+1],vt1,nvt1;
		int i=0,j=0,c1=c;
		Vector3 v,v1;
		k=-90+180/NUM_SEG;
		for(u=0 ;u<=360;u+=360/NUM_SEG)
		{
			p.x=cos(u*Pi)*rad*cos(k*Pi);
			p.z=sin(u*Pi)*rad*cos(k*Pi);
			p.y=sin(k*Pi)*rad;
			vt[j]=ax[0]*p.x+ax[1]*p.y+ax[2]*p.z +_pos;
			nvt[j]=ax[0]*p.x+ax[1]*-p.y+ax[2]*p.z+_pos;
			j++;
		}
		vt1=vt[0];
		for(w=k+180/NUM_SEG;w<=0;w+=180/NUM_SEG)
		{
			j=0;c1=c;
			if(id>8 && w==0) c1=57;
			for(u=0 ;u<=360;u+=360/NUM_SEG)
			{
				p.x=cos(u*Pi)*rad*cos(w*Pi);
				p.z=sin(u*Pi)*rad*cos(w*Pi);
				p.y=sin(w*Pi)*rad;
				p1=ax[0]*p.x+ax[1]*p.y+ax[2]*p.z+_pos;
				np1=ax[0]*p.x+ax[1]*-p.y+ax[2]*p.z+_pos;
				if(j>0)
				{
					v=(vt1-vt[j-1])|(vt[j]-vt[j-1]);v.Unit();
					v1=(nvt1-nvt[j-1])|(nvt[j]-nvt[j-1]);v1.Unit();
					if(v*RDev.SysCamera->ViewDir<0)
					{
						line3(vt[j-1],vt[j],c1);
						line3(vt1,p1,c1);
						line3(vt1,vt[j-1],c1);
						line3(p1,vt[j],c1);
					}
					if(v1*RDev.SysCamera->ViewDir>0)
					{
						line3(nvt[j-1],nvt[j],c1);
						line3(nvt1,np1,c1);
						line3(nvt1,nvt[j-1],c1);
						line3(np1,nvt[j],c1);
					}
					vt[j-1]=vt1;
					nvt[j-1]=nvt1;
				}			
				vt1=p1;
				nvt1=np1;
				j++;
			}
			vt[j-1]=vt1;
			nvt[j-1]=nvt1;
		}
	};
};
static bool bmouse=true;
void HideCur()
{
	bmouse=false;
	while (ShowCursor (FALSE) >= 0){;}
}
void ShowCur()
{
	bmouse=true;
	while (ShowCursor (TRUE) < 0){;}
}
static int SORTBALLCB(const void * b1, const void *b2)
{
	_ball *bl1=(_ball *)b1;
	_ball *bl2=(_ball *)b2;

	Vector3 bp1=bl1->_pos*RDev.SysCamera->ViewMat;
	Vector3 bp2=bl2->_pos*RDev.SysCamera->ViewMat;
	if(bp1.z>bp2.z)return 0;
	else return 1;
}
Vector3 line3c_vp[4];
void SetLClipV(Vector3 p1,Vector3 p2,Vector3 p3,Vector3 p4)
{
	line3c_vp[0]=p1;line3c_vp[1]=p2;line3c_vp[2]=p3;line3c_vp[3]=p4;
}
void line3c(Vector3 p1,Vector3 p2,int clr)
{
	p1=Rasterize(p1);
	p2=Rasterize(p2);
	Vector2 tp1,tp2;
	tp1=Vector2(p1.x,p1.y);
	tp2=Vector2(p2.x,p2.y);
	Vector2 cp[5];
	Vector3 tcp[4];
	
	tcp[0]=line3c_vp[0]*RDev.SysCamera->ViewMat;
	tcp[1]=line3c_vp[1]*RDev.SysCamera->ViewMat;
	tcp[2]=line3c_vp[2]*RDev.SysCamera->ViewMat;
	tcp[3]=line3c_vp[3]*RDev.SysCamera->ViewMat;
	if(tcp[0].z<=0||tcp[1].z<=0||tcp[2].z<=0||tcp[3].z<=0)return;
	tcp[0]=RasterizeEx(tcp[0]);
	tcp[1]=RasterizeEx(tcp[1]);
	tcp[2]=RasterizeEx(tcp[2]);
	tcp[3]=RasterizeEx(tcp[3]);
	cp[0]=Vector2(tcp[0].x,tcp[0].y);
	cp[1]=Vector2(tcp[1].x,tcp[1].y);
	cp[2]=Vector2(tcp[2].x,tcp[2].y);
	cp[3]=Vector2(tcp[3].x,tcp[3].y);
	if(PointInPolygon(tp1,cp,4)
		&&PointInPolygon(tp2,cp,4))return;
	Vector2 tp=(cp[0]+cp[1]+cp[2]+cp[3])/4.0f;
	CpLine(tp1,tp2,cp[0],cp[1],tp);
	CpLine(tp1,tp2,cp[1],cp[2],tp);
	CpLine(tp1,tp2,cp[2],cp[3],tp);
	CpLine(tp1,tp2,cp[3],cp[0],tp);
	line(tp1.x,tp1.y,tp2.x,tp2.y,clr);
}
void line3c1(Vector3 tp1,Vector3 tp2, Vector3 rp01,Vector3 rp02, Vector3 rp11,Vector3 rp12, Vector3 wp1,Vector3 wp2,int c)
{
	tp1=Rasterize(tp1);
	tp2=Rasterize(tp2);
	Vector2 p1=Vector2(tp1.x,tp1.y);
	Vector2 p2=Vector2(tp2.x,tp2.y);
	rp01=rp01*RDev.SysCamera->ViewMat;
	rp02=rp02*RDev.SysCamera->ViewMat;
	rp11=rp11*RDev.SysCamera->ViewMat;
	rp12=rp12*RDev.SysCamera->ViewMat;
	bool r1=true,r2=true;
	if(rp01.z<=0||rp02.z<=0)r1=false;
	if(rp11.z<=0||rp12.z<=0)r2=false;
	rp01=RasterizeEx(rp01);
	rp02=RasterizeEx(rp02);
	rp11=RasterizeEx(rp11);
	rp12=RasterizeEx(rp12);

	Vector2 up01=Vector2(rp01.x,rp01.y);
	Vector2 up02=Vector2(rp02.x,rp02.y);
	Vector2 up11=Vector2(rp11.x,rp11.y);
	Vector2 up12=Vector2(rp12.x,rp12.y);

	wp1=Rasterize(wp1);
	wp2=Rasterize(wp2);
	Vector2 twp1=Vector2(wp1.x,wp1.y);
	Vector2 twp2=Vector2(wp2.x,wp2.y);
	if(r1)CpLine(p1,p2,up01,up02,twp1);
	if(r2)CpLine(p1,p2,up11,up12,twp2);

	line(p1.x,p1.y,p2.x,p2.y,c);
}

class _balldesk
{
public:
	Point3 pos;
public:
	_balldesk(){SetDesk(GTP_AM9);};
	void SetDesk(GAMETYP gtp)
	{
		m_gtp=gtp;
		if(gtp==GTP_SNK)
		{
			dskw=220*0.5f;
			dskh=340*0.5f;
			ballr=BALLR+2;
			ballr1=BALLR+2;
			tr=BALLR+7;
		}
		else if(gtp==GTP_AM9)
		{
			dskw=160*0.5f;
			dskh=240*0.5f;
			ballr=BALLR+2;
			ballr1=BALLR+2;
			tr=BALLR+5;
		}
		else if(gtp==GTP_LUODAI8)
		{
			dskw=160*0.5f;
			dskh=240*0.5f;
			ballr=BALLR+2;
			ballr1=BALLR+2;
			tr=BALLR+5;
		}
		init();
	};
	void init()
	{
		c=57;
		Vector3 x_z=Vector3(1,0,-1);x_z.Unit();
		Vector3 xz=Vector3(1,0,1);xz.Unit();
		axs[0]=Vector3(1,0,0);
-		axs[1]=Vector3(0,-1,0);
		axs[2]=Vector3(0,0,1);
		th=Vector3(0,-ballr*0.8f,0);

		p[0]=Vector3(-dskw,0,dskh);
		p[1]=Vector3(-dskw,0,0);
		p[2]=Vector3(-dskw,0,-dskh);
		p[3]=p[0];		p[4]=p[1];		p[5]=p[2];
		p[3].x=-p[3].x;		p[4].x=-p[4].x;		p[5].x=-p[5].x;
		
		ar1[0]=p[0]+xz*ballr;
		ar2[0]=p[0]+x_z*ballr;
		ar3[0]=p[0]-xz*ballr;
		ar1[1]=ar1[0];		ar2[1]=ar2[0];		ar3[1]=ar3[0];
		ar1[1].x=-ar1[1].x;	ar2[1].x=-ar2[1].x;	ar3[1].x=-ar3[1].x;
		ar1[2]=p[1]-x_z*ballr;
		ar2[2]=p[1]+Vector3(ballr,0,0);
		ar3[2]=p[1]-xz*ballr;
		ar1[3]=ar1[2];		ar2[3]=ar2[2];		ar3[3]=ar3[2];
		ar1[3].x=-ar1[3].x;	ar2[3].x=-ar2[3].x;	ar3[3].x=-ar3[3].x;
		ar1[4]=ar1[0];		ar2[4]=ar2[0];		ar3[4]=ar3[0];
		ar1[4].z=-ar1[4].z;	ar2[4].z=-ar2[4].z;	ar3[4].z=-ar3[4].z;
		ar1[5]=ar1[4];		ar2[5]=ar2[4];		ar3[5]=ar3[4];
		ar1[5].x=-ar1[5].x;	ar2[5].x=-ar2[5].x;	ar3[5].x=-ar3[5].x;

		s[0]=p[0]+xz*ballr;
		t[0]=p[0]+xz*ballr+x_z*tr;
		s[1]=p[0]+xz*ballr+x_z*tr;
		t[1]=s[1];t[1].x=0;
		s[2]=p[0]-xz*ballr;
		t[2]=p[0]-xz*ballr+x_z*tr;
		s[3]=p[0]-xz*ballr+x_z*tr;
		t[3]=p[1]-x_z*ballr+xz*tr;
		s[4]=t[3];
		t[4]=p[1]-x_z*ballr;
		s[5]=s[0];		t[5]=t[0];		s[6]=s[1];		t[6]=t[1];
		s[7]=s[2];		t[7]=t[2];		s[8]=s[3];		t[8]=t[3];
		s[9]=s[4];		t[9]=t[4];		s[5].x=-s[5].x;t[5].x=-t[5].x;
		s[6].x=-s[6].x;t[6].x=-t[6].x;	s[7].x=-s[7].x;t[7].x=-t[7].x;
		s[8].x=-s[8].x;t[8].x=-t[8].x;	s[9].x=-s[9].x;t[9].x=-t[9].x;
		s[10]=s[0];t[10]=t[0];		s[11]=s[1];t[11]=t[1];
		s[12]=s[2];t[12]=t[2];		s[13]=s[3];t[13]=t[3];
		s[14]=s[4];t[14]=t[4];		s[15]=s[5];t[15]=t[5];
		s[16]=s[6];t[16]=t[6];		s[17]=s[7];t[17]=t[7];
		s[18]=s[8];t[18]=t[8];		s[19]=s[9];t[19]=t[9];
		s[10].z=-s[10].z;t[10].z=-t[10].z;		s[11].z=-s[11].z;t[11].z=-t[11].z;
		s[12].z=-s[12].z;t[12].z=-t[12].z;		s[13].z=-s[13].z;t[13].z=-t[13].z;
		s[14].z=-s[14].z;t[14].z=-t[14].z;		s[15].z=-s[15].z;t[15].z=-t[15].z;
		s[16].z=-s[16].z;t[16].z=-t[16].z;		s[17].z=-s[17].z;t[17].z=-t[17].z;
		s[18].z=-s[18].z;t[18].z=-t[18].z;		s[19].z=-s[19].z;t[19].z=-t[19].z;

		lins1[0]=s[0];lins2[0]=t[0];		lins1[1]=s[1];lins2[1]=t[5];
		lins1[2]=t[5];lins2[2]=s[5];		lins1[3]=s[7];lins2[3]=t[7];
		lins1[4]=s[8];lins2[4]=t[8];		lins1[5]=s[9];lins2[5]=t[9];
		lins1[6]=t[19];lins2[6]=s[19];		lins1[7]=t[18];lins2[7]=s[18];
		lins1[8]=t[17];lins2[8]=s[17];		lins1[9]=t[15];lins2[9]=s[15];
		lins1[10]=s[16];lins2[10]=s[11];	lins1[11]=t[10];lins2[11]=s[10];
		lins1[12]=s[12];lins2[12]=t[12];	lins1[13]=s[13];lins2[13]=t[13];
		lins1[14]=s[14];lins2[14]=t[14];	lins1[15]=t[4];lins2[15]=s[4];
		lins1[16]=t[3];lins2[16]=s[3];		lins1[17]=t[2];lins2[17]=s[2];

		actw=ABS(s[4].x);		acth=ABS(s[1].z);
		
		m_dsk.SetPos(Point3(0,0,0));
		m_dsk.SetRect(actw,acth,FLT_MAX);
		for(int i=0;i<18;i++)
		{
			//m_rect[i].Typ(S_OTHER);
			m_rect[i].SetPos(0.5f*(lins1[i]+lins2[i])+Vector3(0,th.y*0.5f,0));
			m_rect[i].SetRect(GetLength(lins1[i],lins2[i])*0.5f,ABS(th.y*0.5f),FLT_MAX);
			m_rect[i]._quat=Quat(Vector3(1,0,0),90.0f*Pi);
		}
		m_rect[0]._quat=m_rect[0]._quat*Quat(Vector3(0,1,0),225*Pi);
		m_rect[1]._quat=m_rect[1]._quat*Quat(Vector3(0,1,0),180*Pi);
		m_rect[2]._quat=m_rect[2]._quat*Quat(Vector3(0,1,0),-225*Pi);
		m_rect[3]._quat=m_rect[3]._quat*Quat(Vector3(0,1,0),-45*Pi);
		m_rect[4]._quat=m_rect[4]._quat*Quat(Vector3(0,1,0),-90*Pi);
		m_rect[5]._quat=m_rect[5]._quat*Quat(Vector3(0,1,0),225*Pi);
		m_rect[6]._quat=m_rect[6]._quat*Quat(Vector3(0,1,0),-45*Pi);
		m_rect[7]._quat=m_rect[7]._quat*Quat(Vector3(0,1,0),-90*Pi);
		m_rect[8]._quat=m_rect[8]._quat*Quat(Vector3(0,1,0),225*Pi);
		m_rect[9]._quat=m_rect[9]._quat*Quat(Vector3(0,1,0),45*Pi);
		m_rect[11]._quat=m_rect[11]._quat*Quat(Vector3(0,1,0),-45*Pi);
		m_rect[12]._quat=m_rect[12]._quat*Quat(Vector3(0,1,0),-225*Pi);
		m_rect[13]._quat=m_rect[13]._quat*Quat(Vector3(0,1,0),90*Pi);
		m_rect[14]._quat=m_rect[14]._quat*Quat(Vector3(0,1,0),45*Pi);
		m_rect[15]._quat=m_rect[15]._quat*Quat(Vector3(0,1,0),-225*Pi);
		m_rect[16]._quat=m_rect[16]._quat*Quat(Vector3(0,1,0),90*Pi);
		m_rect[17]._quat=m_rect[17]._quat*Quat(Vector3(0,1,0),45*Pi);
		

		q1[0]=p[0]+Vector3(0,0,2*ballr);
		q2[0]=p[3]+Vector3(0,0,2*ballr);
		q1[1]=p[0]+Vector3(-2*ballr,0,0);
		q2[1]=p[2]+Vector3(-2*ballr,0,0);
		q1[2]=q1[0];		q2[2]=q2[0];
		q1[2].z=-q1[2].z;	q2[2].z=-q2[2].z;
		q1[3]=q1[1];		q2[3]=q2[1];
		q1[3].x=-q1[3].x;	q2[3].x=-q2[3].x;

		float qw=dskw+2*ballr,qh=dskh+2*ballr;
		SetLClipV(Vector3(-qw,0,qh),Vector3(qw,0,qh),Vector3(qw,0,-qh),Vector3(-qw,0,-qh));
		
		arc1[0]=q1[0];
		arc2[0]=p[0]-x_z*ballr*2;
		arc3[0]=q1[1];
		arc1[1]=arc1[0];		arc2[1]=arc2[0];		arc3[1]=arc3[0];
		arc1[1].x=-arc1[1].x;	arc2[1].x=-arc2[1].x;	arc3[1].x=-arc3[1].x;
		arc1[2]=arc1[0];		arc2[2]=arc2[0];		arc3[2]=arc3[0];
		arc1[3]=arc1[1];		arc2[3]=arc2[1];		arc3[3]=arc3[1];
		arc1[2].z=-arc1[2].z;	arc2[2].z=-arc2[2].z;	arc3[2].z=-arc3[2].z;
		arc1[3].z=-arc1[3].z;	arc2[3].z=-arc2[3].z;	arc3[3].z=-arc3[3].z;
///
		arc1[4]=ar1[0];
		arc2[4]=p[0]-x_z*ballr;
		arc3[4]=ar3[0];
		arc1[5]=ar1[1];
		arc2[5]=p[3]+xz*ballr;
		arc3[5]=ar3[1];
		arc1[6]=arc1[4];	arc2[6]=arc2[4];	arc3[6]=arc3[4];
		arc1[7]=arc1[5];	arc2[7]=arc2[5];	arc3[7]=arc3[5];
		arc1[6].z=-arc1[6].z;	arc2[6].z=-arc2[6].z;	arc3[6].z=-arc3[6].z;
		arc1[7].z=-arc1[7].z;	arc2[7].z=-arc2[7].z;	arc3[7].z=-arc3[7].z;
		
		arc1[8]=ar1[2];
		arc2[8]=p[1]-Vector3(ballr,0,0);
		arc3[8]=ar3[2];
		arc1[9]=arc1[8];		arc2[9]=arc2[8];		arc3[9]=arc3[8];
		arc1[9].x=-arc1[9].x;	arc2[9].x=-arc2[9].x;	arc3[9].x=-arc3[9].x;

		for(i=0;i<6;i++)
		{
			m_cir[i].SetArcSyd(arc1[i+4]+th,arc2[i+4]+th,arc3[i+4]+th,ABS(th.y),FLT_MAX);
		}
		m_hull.Typ(S_HULLPLAN,FLT_MAX);
		for(i=0;i<6;i++)
			m_hull.mp[i]=p[i];
		m_hull.rad=ballr;

		m_rects.Typ(S_OTHER+1,FLT_MAX);
	};
	void DrawDesk()
	{	
		Vector3 tbh=Vector3(0,80,0);
		float tbw1=20,tbh1=20;
		tv[0]=Vector3(0,0,0)+Vector3(-dskw,0,dskh)+Vector3(20,0,-40);
		tb[0]=tv[0]+Vector3(-tbw1,0,tbh1);
		tb[1]=tv[0]+Vector3(tbw1,0,tbh1);
		tb[2]=tv[0]+Vector3(tbw1,0,-tbh1);
		tb[3]=tv[0]+Vector3(-tbw1,0,-tbh1);
		
		tb[4]=tb[0];		tb[5]=tb[1];		tb[6]=tb[2];		tb[7]=tb[3];
		tb[4].x=-tb[4].x;	tb[5].x=-tb[5].x;	tb[6].x=-tb[6].x;	tb[7].x=-tb[7].x;
		tb[8]=tb[0];	tb[9]=tb[1];	tb[10]=tb[2];	tb[11]=tb[3];
		tb[12]=tb[4];	tb[13]=tb[5];	tb[14]=tb[6];	tb[15]=tb[7];
		tb[8].z=-tb[8].z;	tb[9].z=-tb[9].z;	tb[10].z=-tb[10].z;	tb[11].z=-tb[11].z;
		tb[12].z=-tb[12].z;	tb[13].z=-tb[13].z;	tb[14].z=-tb[14].z;	tb[15].z=-tb[15].z;

		int i;
		Vector3 vfg=Vector3(0,0,0);
		if(RDev.SysCamera->ViewDir*axs[2] >=0){	line3(q1[2],q2[2],c);	vfg.z=-1;}
		else 	{	line3(q1[0],q2[0],c);	vfg.z=1;}
		if(RDev.SysCamera->ViewDir*axs[0] >=0){	line3(q1[1],q2[1],c);	vfg.x=-1;}
		else 	{	line3(q1[3],q2[3],c);	vfg.x=1;}
		if(vfg.z==1||vfg.x==1)		ArcP(arc1[1],arc2[1],arc3[1],c);
		if(vfg.z==-1||vfg.x==1)		ArcP(arc1[3],arc2[3],arc3[3],c);
		if(vfg.z==-1||vfg.x==-1)	ArcP(arc1[2],arc2[2],arc3[2],c);
		if(vfg.z==1||vfg.x==-1)		ArcP(arc1[0],arc2[0],arc3[0],c);
		
		for(i=0;i<18;i++)line3(lins1[i]+th,lins2[i]+th,c);
		for(i=0;i<4;i++)
		{
			line3(q1[i]+th,q2[i]+th,c);
			ArcP(arc1[i]+th,arc2[i]+th,arc3[i]+th,c);
		}
		for(i=0;i<6;i++)
		{
//			ArcP(ar1[i],ar2[i],ar3[i],30);
			DrawCircle(p[i],axs,BALLR+2,c);
			ArcP(arc1[i+4]+th,arc2[i+4]+th,arc3[i+4]+th,c);
		}
		if(m_gtp==GTP_SNK)
		{
			float f23h=0.6f*acth;
			line3c1(Vector3(-actw,0,-f23h),Vector3(actw,0,-f23h),
				lins1[7]+th,lins2[7]+th, lins1[13]+th,lins2[13]+th,
				lins1[7]+th+Vector3(ballr,0,0),lins1[13]+th+Vector3(-ballr,0,0),c);
			DrawCircle(Vector3(0,0,-f23h),axs,2,c);
			ArcP(Vector3(8*BALLR,0,-f23h),Vector3(0,0,-f23h-8*BALLR),Vector3(-8*BALLR,0,-f23h),c);
		}
		for(i=0;i<18;i++)
			_DrawBody(&m_rect[i],c);
		//for(i=0;i<6;i++)
		//_DrawBody(&m_cir[i],1);

		float sgz,sgx;
		sgz=-SIGN(axs[2]*RDev.SysCamera->ViewDir);
		sgx=-SIGN(axs[0]*RDev.SysCamera->ViewDir);

		if(sgz>0){line3c(tb[0],tb[0]+tbh,c);	line3c(tb[1],tb[1]+tbh,c);	line3c(tb[0]+tbh,tb[1]+tbh,c);}
		if(sgx>0){line3c(tb[1],tb[1]+tbh,c);	line3c(tb[2],tb[2]+tbh,c);	line3c(tb[1]+tbh,tb[2]+tbh,c);}
		if(sgz<0){line3c(tb[2],tb[2]+tbh,c);	line3c(tb[3],tb[3]+tbh,c);	line3c(tb[2]+tbh,tb[3]+tbh,c);}
		if(sgx<0){line3c(tb[3],tb[3]+tbh,c);	line3c(tb[0],tb[0]+tbh,c);	line3c(tb[3]+tbh,tb[0]+tbh,c);}
///
		if(sgz>0){line3c(tb[4],tb[4]+tbh,c);	line3c(tb[5],tb[5]+tbh,c);	line3c(tb[4]+tbh,tb[5]+tbh,c);}
		if(sgx<0){line3c(tb[5],tb[5]+tbh,c);	line3c(tb[6],tb[6]+tbh,c);	line3c(tb[5]+tbh,tb[6]+tbh,c);}
		if(sgz<0){line3c(tb[6],tb[6]+tbh,c);	line3c(tb[7],tb[7]+tbh,c);	line3c(tb[6]+tbh,tb[7]+tbh,c);}
		if(sgx>0){line3c(tb[7],tb[7]+tbh,c);	line3c(tb[4],tb[4]+tbh,c);	line3c(tb[7]+tbh,tb[4]+tbh,c);}
///	
		if(sgz<0){line3c(tb[8],tb[8]+tbh,c);	line3c(tb[9],tb[9]+tbh,c);	line3c(tb[8]+tbh,tb[9]+tbh,c);}
		if(sgx>0){line3c(tb[9],tb[9]+tbh,c);	line3c(tb[10],tb[10]+tbh,c);line3c(tb[9]+tbh,tb[10]+tbh,c);}
		if(sgz>0){line3c(tb[10],tb[10]+tbh,c);	line3c(tb[11],tb[11]+tbh,c);line3c(tb[10]+tbh,tb[11]+tbh,c);}
		if(sgx<0){line3c(tb[11],tb[11]+tbh,c);	line3c(tb[8],tb[8]+tbh,c);	line3c(tb[11]+tbh,tb[8]+tbh,c);}
///
		if(sgz<0){line3c(tb[12],tb[12]+tbh,c);	line3c(tb[13],tb[13]+tbh,c);line3c(tb[12]+tbh,tb[13]+tbh,c);}
		if(sgx<0){line3c(tb[13],tb[13]+tbh,c);	line3c(tb[14],tb[14]+tbh,c);line3c(tb[13]+tbh,tb[14]+tbh,c);}
		if(sgz>0){line3c(tb[14],tb[14]+tbh,c);	line3c(tb[15],tb[15]+tbh,c);line3c(tb[14]+tbh,tb[15]+tbh,c);}
		if(sgx>0){line3c(tb[15],tb[15]+tbh,c);	line3c(tb[12],tb[12]+tbh,c);line3c(tb[15]+tbh,tb[12]+tbh,c);}
///	
	};
public:
	Vector3 tb[8*4],tv[4];
	Vector3 arc1[10],arc2[10],arc3[10];	
	Vector3 q1[4],	q2[4];
	Vector3 ar1[10],ar2[10],ar3[10];
	Vector3 s[20],t[20];
	Vector3 axs[3];
	Vector3 p[6];
	Vector3 th;

	Vector3 lins1[18],lins2[18];
	Body m_rect[18],m_dsk,m_rects;
	Body m_cir[6],m_hull;
	float dskw,dskh,actw,acth;
	float ballr,ballr1,tr;
	int c;
	GAMETYP m_gtp;
};
void linex(Vector2 p1,Vector2 p2, int c,float sg=4,float sp=2)
{
	Vector2 pv=p2-p1;
	float l=sqrtf(pv*pv);	pv.Unit();
	if(l<sg)return;
	sg=l/(float)((int)(l/sg));
	float sgp=sg-sp;
	DWORD dw=(GetTickCount()/100)%(int)sg;
	float s=(float)dw;
	float t=0;
	if(s>sgp)t=sgp;
	else t=s;
	Vector2 t1,t2;
	t1=p1+s*pv;
	t2=p1+(s-t)*pv;
	line(t1.x,t1.y,t2.x,t2.y,c);
	for (float i=s+sg;i<l;i+=sg)
	{
		t1=p1+i*pv;
		t2=p1+(i-sgp)*pv;
		line(t1.x,t1.y,t2.x,t2.y,c);
	}
	if(s>=0&&s<sgp)
	{
		t=sgp-s;
		t1=p1+l*pv;
		t2=p1+t*pv;
		line(t1.x,t1.y,t2.x,t2.y,c);
	}
}

void linex(Vector3 p1,Vector3 p2,int c,float sg=4,float sp=2)
{
	Vector3 pv=p2-p1;
	float l=sqrtf(pv*pv);	pv.Unit();
	if(l<sg)return;
	sg=l/(float)((int)(l/sg));
	float sgp=sg-sp;
	DWORD dw=(GetTickCount()/100)%(int)sg;
	float s=(float)dw;
	float t=0;
	if(s>sgp)t=sgp;
	else t=s;
	Vector3 t1,t2;
	t1=p1+s*pv;
	t2=p1+(s-t)*pv;
	line3(t1,t2,c);
	for (float i=s+sg;i<l;i+=sg)
	{
		t1=p1+i*pv;
		t2=p1+(i-sgp)*pv;
		line3(t1,t2,c);
	}
	if(s>=0&&s<sgp)
	{
		t=sgp-s;
		t1=p1+l*pv;
		t2=p1+(l-t)*pv;
		line3(t1,t2,c);
	}
}
bool GetInsInElsLine(Vector3 o,float a,float b, Vector3 q,Vector3 v,Vector3 &ins)
{
	float _a,_b,_c,_d;
	_a=SQR(b*v.x)+SQR(a*v.y);
	_b=2*q.x*v.x*b*b+2*q.y*v.y*a*a;
	_c=SQR(q.x*b)+SQR(q.y*a)-SQR(a*b);
	_d=_b*_b-4.0f*_a*_c;
	if(_d<0)return false;
	float t=-(_b-sqrtf(_d))/(2*_a);
	ins=q+v*t;
	return true;
}
bool RayLineIns(Vector2 o,Vector2 v, Vector2 p1,Vector2 p2, Vector2& ins)
{
	Vector2 av,bv,an,bn;
	av=v;
	bv=p2-p1;//bv.Unit();
	an=av^1;	an.Unit();
	bn=bv^1;	bn.Unit();
	Vector2 c0,c1;
	float s,t,e,f;
	c0=p1-o;	c1=o-p1;
	e=av*bn;	f=bv*an;
	if(e==0||f==0)return false;
	s=(c0*bn)/e;
	t=(c1*an)/f;
	if(t<0||t>1)return false;
	if(s<0)return false;
	ins=o+av*s;
	return true;
}
class _tick:public Body
{
public:
	char clr;
	_ball *balls;
	_balldesk *balldsk;
	float def;//横向角度
	float hef;//纵向角度
	float l_hef,l_pullr;//纵向角度极限,移杆极限
	float pulls,pulll;//拉杆位置，拉杆距离
	float zooml;
	Vector3 tpos;//位置
	Vector3 ball0;//白球位置
	Vector3 axs[3];
	Vector3 pullr;//击球位置
	Vector3 pullp;//击球点
	Vector3 pulldir;//描线方向
	Quat qtd,qth;
	int tochedball,tochedballl;
	int numballs;
	GAMETYP m_gtp;
	float tickh;
	float speed;
	float starts;//开始击球的拉杆距离
	DWORD starttime;
	Vector3 tipline[10];
	int numtipline,tipball;
	bool showtip;
	int cammode,opmode;
	Vector3 camvec,campos,cmvc[3],cmps;
	float cmhd,cmfd;
	float camh;
	bool bready;
	bool boundcam;
	Vector3 ctrl2dp;
	Vector2 ctrl2mouse;

	Vector3 oldball0;
	LONG bartime,tracetime;
	int tracing;
	LONG forcereadytime,frtime;

	_gdata *gdt;
public:
	_tick(){init();};
	bool GetReady(){return bready;};
	bool IsTracing(){return (tracing==1);};
	void Impuls()
	{
		pullr=Vector3(0,0,0);
		float invms=1.0f/(balls[0].invMass + 1.0f/100.0f);
		Vector3 force=axs[1]*speed*invms * gdt->impulls;

		Vector3 rr;
		rr=pullp-balls[0]._pos;
		balls[0]._torque=force|rr;
		rr.Unit();
		balls[0]._force=-axs[1]*(force*rr);
		if(hef<8 && pullp.y>-0.9f)
		{
			balls[0]._force.y=-force*rr*1.0f;
		}

		bready=false;
		forcereadytime=GetTickCount();
		frtime=0;
		if(gdt)
			gdt->mousebar=0;
	};
	void SetReady()
	{
		if(bready)return;
		bready=true;
		if(boundcam==true)
			tracetime=GetTickCount();
		else 
		{
			tracetime=-1;
			tracing=0;
			ball0=balls[0]._pos;
		}
		oldball0=ball0;
		//ball0=balls[0]._pos;
		pullr=Vector3(0,0,0);
		pulls=TICKH/2.0f * 0.1f;
		bartime=-1;
		forcereadytime=-1;
		frtime=-1;
		speed=0;
		gdt->mousebar=0;
		updata(0,0);
	}
	void RotateCamByMouse(float dx,float dy)
	{
		if(cammode==2)return;
		cmhd+=dy/100;
		cmfd+=dx/100;
		if(cmhd>0)cmhd=0;
		else if(cmhd<-90.0f)cmhd=-90.0f;
		cmfd=(int)(cmfd)%360;
		Vector3 tmvc[3];
		Quat qf=Quat(Vector3(0,1,0),cmfd*Pi);
		//cmps=campos*qf;
		cmps=Vector3(1,-0.5f,0)*250*qf;
		tmvc[0]=Vector3(0,1,0)*qf;//cmvc[0]*qf;
		tmvc[1]=Vector3(1,0,0)*qf;//cmvc[1]*qf;
		tmvc[2]=Vector3(0,0,1)*qf;//cmvc[2]*qf;
		Quat qh=Quat(tmvc[0],cmhd*Pi);
		cmps=cmps*qh;
		tmvc[0]=tmvc[0]*qh;
		tmvc[1]=tmvc[1]*qh;
		tmvc[2]=tmvc[2]*qh;
		
		RDev.SysCamera->LookAt(cmps,-cmps,tmvc[0]);
	}
	void calccolid()//计算碰撞
	{
		Vector3 ps1=tpos;
		Vector3 ps2=tpos+axs[1]*tickh;
		Vector2 ins; Vector3 ins3;
		float g=balldsk->th.y;
		float r1=TICKR,r2=TICKR+2;
		Vector3 v1=axs[1]*tickh+axs[2]*r2;
		float tka=GetAngel(axs[1],v1);
		float tkb=0;
		float t=1.0f/(axs[2]*Vector3(0,1,0));	
		Vector3 t1=ps1+axs[2]*r1;
		Vector3 t2=ps2+axs[2]*r2;
		float ar,br,cr;
		bool bfound=false,bout=false;
		for(int i=0;i<18;i++)
		{
			Vector2 l1,l2,k1,k2;
			l1=Vector2(balldsk->lins1[i].x,balldsk->lins1[i].z);
			l2=Vector2(balldsk->lins2[i].x,balldsk->lins2[i].z);
			k1=Vector2(t1.x,t1.z);
			k2=Vector2(t2.x,t2.z);
			if(Get2LInsect(l1,l2,k1,k2,&ins))
			{
				bfound=true;
				ins3=Vector3(ins.x,g,ins.y);
				cr=GetLD(ins3, t1, t2);
				ar=ABS(r1*ps1.y*t*r1-r1);
				l_pullr=MIN(ar,cr);
				tkb=GetAngel(ins3-ball0,-pulldir);
				l_hef=tka+tkb;
				break;
			}
			if(RayLineIns(k1,k2-k1,l1,l2,ins))
			{
				ins3=Vector3(ins.x,g,ins.y);
				tkb=GetAngel(ins3-ball0,-pulldir);
				l_hef=tka+tkb;
				break;
			}
		}
		if(!bfound)
		{
			if(t1.x<-balldsk->actw || t1.x>balldsk->actw 
				|| t1.z<-balldsk->acth || t1.z>balldsk->acth)
				bout=true;
			if(t2.x<-balldsk->actw || t2.x>balldsk->actw 
				|| t2.z<-balldsk->acth || t2.z>balldsk->acth)
				bout=true;
			if(bout==false)
			{
				ar=ABS(r1*ps1.y*t*r1-r1);
				br=ABS(r2*ps2.y*t*r2-r2);
				l_pullr=MIN(ar,br);
				l_hef=0;
			}
			else 
			{
				l_pullr=ABS(r1*(ps1.y-g)*t*r1-r1);
				l_hef=-(tka+tkb);
			}
		}
	};
	void gentipball()
	{
		int iballs[22];
		int bj=0;
		memset(iballs,0,sizeof(int)*22);
		Vector3 bv;
		float balll=0,minl=1000;
		tochedball=0;
		for(int i=1;i<numballs;i++)
		{
			if(balls[i].bjind==true)continue;
			if(balls[i].enable==false)continue;
			bv=balls[i]._pos-ball0;
			balll=bv*axs[0];
			if(ABS(balll)<2*BALLR)
			{
				iballs[bj++]=i;
			}
		}
		for(i=0;i<bj;i++)
		{
			bv=balls[iballs[i]]._pos-ball0;
			balll=bv*pulldir;
			if(balll>0 && balll<minl)
			{
				minl=balll;
				tochedball=iballs[i];
				tochedballl=bv*axs[0];
			}
		}
	}
	void gentipline(int nl=2)
	{
		int j,ls=1;
		Vector3 q=ball0;
		Vector3 qv=pulldir;
		Vector3 ins,minins;
		Vector2 o=Vector2(ball0.x,ball0.z);
		Vector2 dv=Vector2(pulldir.x,pulldir.z);
		Vector2 l1,l2,ins2,ln;
		float tt=0,mintt=2000;
		tipline[0]=ball0+pulldir*BALLR;
		tipball=0;
		for(int i=0;i<nl;i++)
		{
			for(j=1;j<numballs;j++)
			{
				if(balls[j].bjind==true)continue;
				if(balls[j].enable==false)continue;
				if(GetInsectLS(q,qv,balls[j]._pos,BALLR,ins,&tt))
				{
					if(tt<mintt){mintt=tt;minins=ins;tipball=j;}
				}
			}
			if(mintt!=2000)
			{
				tipline[ls++]=minins;
				break;
			}
			for(j=0;j<6;j++)
			{
				if(GetInsectLS(q,qv,balldsk->p[j]+Vector3(0,-BALLR,0),BALLR,ins))
				{
					tipline[ls++]=ins;
					numtipline=ls;
					return;
				}
			}
			for(j=0;j<18;j++)
			{
				l1=Vector2(balldsk->lins1[j].x,balldsk->lins1[j].z);
				l2=Vector2(balldsk->lins2[j].x,balldsk->lins2[j].z);
				if(RayLineIns(o,dv,l1,l2,ins2))
				{
					ln=l1-l2;ln=ln^-1;ln.Unit();	ln=ln*BALLR;
					tipline[ls++]=Vector3(ins2.x,-BALLR,ins2.y)+Vector3(ln.x,0,ln.y);
					o=ins2+ln;
					dv=GetVecInvers(dv,ln);
					q=Vector3(o.x,-BALLR,o.y);
					qv=Vector3(dv.x,0,dv.y);
					break;
				}
			}
		}
		numtipline=ls;
	};
	void SetTick(GAMETYP gtp)
	{
		m_gtp=gtp;
		if(gtp==GTP_SNK)
		{
			tickh=TICKH;
			numballs=22;
		}
		else if(gtp==GTP_AM9)
		{
			tickh=100;
			numballs=10;
		}
		else if(gtp==GTP_LUODAI8)
		{
			tickh=100;
			numballs=16;
		}
	}
	void SetCamMode(int d)
	{	
		cammode=d;
		if(cammode==2)
			boundcam=false;
		else boundcam=true;
	};
	void SetOpMode(int o)
	{
		opmode=o;
	};
	int getopr(){return opmode;};
	void init()
	{
		SetTick(GTP_AM9);
		SetCamMode(2);
		gdt=NULL;
		tracing=0;
		bartime=-1;tracetime=-1;
		cmhd=cmfd=0;opmode=0;
		ctrl2mouse=Vector2(WIDTH*0.5f,HEIGHT*0.5f);
		showtip=false;boundcam=true;
		camh=50; bready=true;
		pulls=TICKH/2.0f * 0.1f;	pulll=TICKH/2.0f;
		l_hef=0;	l_pullr=BALLR;	def=0;
		hef=0;	tochedball=0;tipball=0;numtipline=0;
		zooml=100; speed=0;starts=0;starttime=0;
		balls=NULL;
		balldsk=NULL;
		_quat=Quat(Vector3(1,0,0),-90*Pi);
		axs[0]=_Axis[0]*_quat;
		axs[1]=_Axis[1]*_quat;
		axs[2]=_Axis[2]*_quat;
		qtd=qth=Quat();
		cmhd=-10;
		forcereadytime=-1;
		frtime=-1;
	};
	void Create(_ball *b,_balldesk *dsk,_gdata *gt)
	{
		balls=b;balldsk=dsk;
		_pos=b[0]._pos;
		ball0=_pos;
		gdt=gt;
		updata(0,0);
	};
	void traceball()//移动ball0(相当于移动相机)
	{
		int dtime;
		if(tracetime>0)
		{
			dtime=(GetTickCount()-tracetime)/20;
			Vector3 lv=balls[0]._pos-oldball0;
			float ll=lv.Mod();lv.Unit();
			if(dtime>ll)
			{
				tracetime=-1;
				tracing=0;
				ball0=balls[0]._pos;
				return;
			}
			tracing=1;
			//float sh=ll/20.0f;
			float sl=dtime;//dtime*sh;
			ball0=oldball0+lv*sl;
		}else{tracing=0;ball0=balls[0]._pos;}
		return;
	};
	void drawtick()
	{
		if(forcereadytime!=-1)
		{
			frtime=GetTickCount()-forcereadytime;
			if(frtime>60000)
			{
				if(!bready)
				{
					for(int i=0;i<numballs;i++)
					{
						balls[i].clearmove();
					}
				}
				forcereadytime=-1;
				frtime=-1;
			}
		}
		if(getkey('C',true))boundcam=!boundcam;
		if(getkey('A') && !rmclked && !lmclked)
		{
			camh+=3;
			if(camh>100)camh=100;
			bindcam();
		}
		else if(getkey('Z') && !rmclked && !lmclked)
		{
			camh-=3;
			if(camh<0)camh=0;
			bindcam();
		}
		if(getkey('4',true))opmode=!opmode;

		if(!bready)return;
		traceball();
		if(tracing==1)return;
		if(cammode==2 && !getkey(VK_CONTROL))
		{
			DrawSphere1(ctrl2dp,_Axis,BALLR,57);
			linex(ball0,ctrl2dp,22);
		}
		if(getkey('T',true))showtip=!showtip;
		if(showtip)
		{
			for(int i=0;i<numtipline-1;i++)
				linex(tipline[i],tipline[i+1],22,10);
			if(tipball)balls[tipball].DrawCir();
		}
		tpos=ball0+axs[1]*BALLR+axs[1]*pulls+pullr.x*axs[0]+pullr.z*axs[2];
		if(GetInsectLS(tpos,-axs[1], ball0, BALLR,pullp))
		{
			Vector3 ax[3];
			ax[1]=pullp-ball0;ax[1].Unit();
			ax[0]=Vector3(0,1,0);
			ax[2]=ax[1]|ax[0];ax[2].Unit();
			ax[0]=ax[2]|ax[1];ax[0].Unit();
			DrawCircle(pullp,ax,0.5f,22);
		}
		DrawSylind(tpos,axs,TICKR,tickh,57);
	};
	void drawballtip()
	{
		if(!bready || tracing==1)return;
		Vector2 pt,ps;
		ps=Vector2(340,250);
		float r1=20;
		float rf=r1/BALLR;
		pt.x=rf*pullr.x;
		pt.y=rf*pullr.z;
		Circle(ps.x,ps.y,r1,57);
		FillCircle(ps.x,ps.y,r1-1,0);
		Circle(ps.x,ps.y,2,57);
		ps+=pt;
		FillCircle(ps.x,ps.y,2,22);

		if(tochedball!=0)
		{
			ps.x=tochedballl*rf;
			ps.y=-sqrtf(r1*r1*4-ps.x*ps.x);
			ps+=Vector2(340,250);
			Circle(ps.x,ps.y,r1,balls[tochedball].c);
			FillCircle(ps.x,ps.y,r1-1,0);
		}
		linex(Vector2(340,250)+Vector2(-r1,0),Vector2(340,250)+Vector2(-r1,-40),57,3,2);
		linex(Vector2(340,250)+Vector2(r1,0),Vector2(340,250)+Vector2(r1,-40),57,3,2);
		
	};
	void drawspeedbar()
	{
		if(!bready || tracing==1||bmouse==true)return;
		if(!getkey(VK_CONTROL) && gdt->mousebar==0)
		{
			bartime=-1;
			return;
		}
		else if(getkey(VK_CONTROL))
		{
			gdt->mousebar=0;
		}
		float bh=150;
		float sh=bh/pulll *(pulll-pulls)+1;
		Line_(10,215-bh-1, 20,215, 57, true);
		if(opmode==0)FillLine(11,215-sh+1, 19,214, 22);
		else FillLine(11,215-sh+1, 19,214, 1);
		
		if(opmode==1)
		{
			static int fg=0;
			static int shoot=0;
			int tm,ps=0;
			if(bartime==-1)	{fg=0;shoot=0;bartime=GetTickCount();	}
			if(shoot==0)
			{
				tm=(GetTickCount()-bartime)/40;
				if(tm>pulll)
				{
					tm=tm%(int)pulll;
					bartime=GetTickCount();
					fg=!fg;
				}
				if(fg==0)	{	pulls=tm;	}
				else if(fg==1)	{	pulls=pulll-tm;	}
			}
			else //shoot
			{
				tm=(GetTickCount()-bartime)/5;
				pulls-=tm;
				if(pulls<0)
				{
					pulls=0;
					bartime=-1;
					speed=(pulll-ps)/80.0f *1000.0f;
					if(speed>0)
					{
						Impuls();
					}
				}
			}
			if(bmouse==false)
			{
				if(lmclked)
				{
					shoot=1;
					ps=pulls;
					bartime=GetTickCount();
				}
				else 
				{
					shoot=0;
				}
			}
		}
	};
	void zoomcam(float dltz)
	{
		zooml+=dltz*20;
		if(zooml<0)zooml=0;
		else if(zooml>350)zooml=350;
		updata(0,0);
	}
	void bindcam()
	{
		cmfd=cmhd=0;
		RDev.SysCamera->LookAt(campos,camvec,axs[2]);
	}
	void updata(float mx,float my)
	{
		mx*=gdt->mouserev;
		my*=gdt->mouserev;
		//if(!bready)return;
		if(!getkey(VK_CONTROL) && gdt->mousebar==0)
		{
			if(gdt->bcheckstickcollid && tracing==0 && bready)	calccolid();
			if(lmclked && bready)
			{
				if(!rmclked)
				{
					float prx=mx/10.0f;
					float prz=my/10.0f;
					pullr+=Vector3(prx,0,prz);
					if(pullr.z>l_pullr)pullr.z=l_pullr;
					if(sqrtf(pullr*pullr)>BALLR-0.1f)
					{
						Vector3 u=pullr;u.Unit();
						pullr=u*(BALLR-0.1f);
					}
				}
				else// rmclked
				{
					pullr=Vector3(0,0,0);
				}
			}
			else if(frtime==-1 || frtime>1000)
			{
				if(cammode==3)
				{
					float sdf,shf;
					if(!getkey(VK_SHIFT))
					{
						sdf=-mx/10.0f ;
						shf=-my/10.0f ;
					}
					else
					{
						sdf=-mx/80.0f ;
						shf=-my/80.0f ;
					}
					def+=sdf;
					def=(int)(def)%360;
					
					hef+=shf;
					if(hef>90)hef=90;
					else if(hef<l_hef)hef=l_hef;

					axs[0]=_Axis[0]*_quat;
					axs[1]=_Axis[1]*_quat;
					axs[2]=_Axis[2]*_quat;

					qtd=Quat(Vector3(0,1,0),def*Pi);
					axs[0]=axs[0]*qtd;
					axs[1]=axs[1]*qtd;
					axs[2]=axs[2]*qtd;
					
					qth=Quat(axs[0],-hef*Pi);
					axs[0]=axs[0]*qth;
					axs[1]=axs[1]*qth;
					axs[2]=axs[2]*qth;	

					camvec=axs[1]*tickh - axs[0]*10.0f -axs[2]*camh;
					camvec.Unit();
					campos=ball0+camvec*(zooml+20);
					camvec=-camvec;
					
					cmvc[1]=-campos;cmvc[1].Unit();
					cmvc[2]=axs[2];
					cmvc[0]=cmvc[2]|cmvc[1];
					cmvc[2]=cmvc[1]|cmvc[0];
					
					if(boundcam)bindcam();
				}
				else if(cammode==2)
				{
					ctrl2mouse+=Vector2(mx/10.0f, my/10.0f);
					RayT rt=RDev.GetMouseVec(ctrl2mouse.x,ctrl2mouse.y);
					if(GetInsectInTri(rt.start,rt.end,balldsk->p[0],balldsk->p[1],balldsk->p[3],ctrl2dp))
					{
						if(ctrl2dp.x<-(balldsk->actw-BALLR))ctrl2dp.x=-(balldsk->actw-BALLR);
						if(ctrl2dp.x>(balldsk->actw-BALLR))ctrl2dp.x=(balldsk->actw-BALLR);
						if(ctrl2dp.z<-(balldsk->acth-BALLR))ctrl2dp.z=-(balldsk->acth-BALLR);
						if(ctrl2dp.z>(balldsk->acth-BALLR))ctrl2dp.z=(balldsk->acth-BALLR);
						Vector3 cc=Rasterize(ctrl2dp);
						ctrl2mouse=Vector2(cc.x,cc.y);
						ctrl2dp.y=-BALLR;
						axs[1]=ball0-ctrl2dp;axs[1].Unit();
						axs[2]=Vector3(0,1,0);
						axs[0]=axs[1]|axs[2];axs[0].Unit();
						float xg=GetAngel(axs[0],Vector3(1,0,0));
						if(axs[0]*Vector3(0,0,1)>0)	xg=360-xg;
						def=xg;
					}
					if(tochedball!=0)
					{
						float tt1=sqrtf(4*BALLR*BALLR-tochedballl*tochedballl);
						Vector3 tt=balls[tochedball]._pos-axs[0]*(tochedballl+0.4f)-pulldir*tt1;
						Vector3 vd=ctrl2dp-ball0;
						Vector3 vt=tt-ball0;
						Vector3 vtn=vt;vtn.Unit();
						if(sqrtf(vt*vt) < vd*vtn)
						{
							ctrl2dp=tt;
							tt=Vector3(ctrl2dp.x,0,ctrl2dp.z);
							tt=Rasterize(tt);
							ctrl2mouse=Vector2(tt.x,tt.y);
						}
						else
						{
						}
					}
				}
			}
			pulldir=-axs[1];
			pulldir.y=0;
			pulldir.Unit();
			gentipball();
			gentipline(2);

		}
		else if(bmouse==false && bready && tracing==0)
		{
			if(!rmclked && !lmclked && opmode==0)
			{
				float spl=my/1.0f;
//				char vv[10];memset(vv,0,sizeof(char)*10);
//				sprintf(vv,"%d \n",(int)spl);
//				OutputDebugString(vv);
				pulls+=spl;
				if(pulls<0)
				{
					pulls=0;
					speed=starts/(float)(GetTickCount()-starttime)*1000.0f;
					//pullr=Vector3(0,0,0);
					if(speed>0)
					{
						Impuls();
					}
				}
				else if(pulls>pulll)pulls=pulll;
				if(spl>0)
				{
					starts=pulls;
					starttime=GetTickCount();
				}
			}
		}
	};
};

class _player
{
public:
	int level;
public:

};

class GameEffect
{
public:
	_player *pdt;
	_gdata *gdt;
	NODE<Eftstr *> Eftlst;
public:
	GameEffect()
	{
		gdt=NULL;
		pdt=NULL;
	}
	void SetGdt(_gdata *gt){gdt=gt;}
	void SetPdt(_player *pt){pdt=pt;}
	void Effectloop()
	{
		Eftstr *eftstr;
		bool bres=true;
		for(eftstr=Eftlst.GetFirst();eftstr!=NULL;eftstr=Eftlst.GetNext())
		{
			switch(eftstr->Eftp)
			{
			case EFT_SCR:{bres=loopdoscr(eftstr);break;}
			}
			if(bres==false)
			{
				Eftlst.Delete();//非物理删除;
				delete eftstr;
				dels+=1;
			}
		}
	};
	void Effectdestroy(){Eftlst.Free();};
	void startdoscr(int sc);
	bool loopdoscr(Eftstr *eft);
};

static float m_e,m_friction,m_impulls,m_timstep,m_fps,m_bcheckstickcollid,m_mouserev;
void CALLBACK uicbproc( UINT nEvent, int nControlID, UIControl* pControl ,void * mdata)
{
	_gdata *gdt=(_gdata*)mdata;
	switch(nEvent)
	{
	case EVENT_CHECKBOX_CHANGED:
		{
			UICheckBox *cb=(UICheckBox*)pControl;
			m_bcheckstickcollid=cb->GetChecked()?1:0;
		}
		break;
	case EVENT_BUTTON_CLICKED:
		{
			if(nControlID==7)//ok
			{
				gdt->bcheckstickcollid=m_bcheckstickcollid;
				gdt->e=m_e;
				gdt->friction=m_friction;
				gdt->impulls=m_impulls;
				gdt->fps=m_fps;
				gdt->timstep=m_timstep;
				gdt->mouserev=m_mouserev;
				pControl->m_pDialog->SetVisible(false);
				pControl->m_pDialog->ClearFocus();
			}
			else if(nControlID==8)//cancel
			{
				pControl->m_pDialog->SetVisible(false);
				pControl->m_pDialog->ClearFocus();
			}
		}
		break;
	case EVENT_SLIDER_VALUE_CHANGED:
		{
			UISlider *sl=(UISlider*)pControl;
			if(nControlID==1)//fps
			{
				m_fps=sl->GetValue();
			}
			else if(nControlID==2)//time step
			{
				m_timstep=(float)sl->GetValue()/1000.0f;
			}
			else if(nControlID==3)//e
			{
				m_e=(float)sl->GetValue()/100.0f;
			}
			else if(nControlID==4)//friction
			{
				m_friction=(float)sl->GetValue()/100.0f;
			}
			else if(nControlID==5)//impulls
			{
				m_impulls=(float)sl->GetValue()/20.0f;
			}
			else if(nControlID==9)//mouse
			{
				m_mouserev=(float)sl->GetValue()/100.0f;
			}
		}
		break;
	}

}
void print_fnum(int x,int y,float n,int c ,char tx[]="%.3f")
{
	char tt[10];
	memset(tt,0,sizeof(char)*10);
	sprintf(tt,tx,n);
	print_string(x,y,c,tt);
}
class ZuoQiu
{
public:
	_balldesk balldesk;
	_ball ball[22],bkball[22];
	_tick balltick,bkballtick;

	Camera maincam,cam2d,smallcam[6],smallcam2d;
	 _ball *balllst[22];
	 int currballs;//当前游戏类型下是多少个球
	 _ball* pickedball;
	 UIDialog m_smallwindlg,m_helpdlg,m_configdlg;
	 int cammode;
	World m_world,m_xumuwd;
	Body xumuball[7],xumurect;
	Joint xumujt[7];
	GameEffect Eft;	//特效管理
	CManager_Time MTime; //时间管理
	CameraList CMLst; //相机管理

	_gdata gdata;	//游戏数据
	_player pdt[2];	//玩家类

	int turnsaved;
	int mnuidx,mnuidx1;
	int pickmode,pickspc;
	int trainmode,mousemode;
	int ballcanpullid;//可以击打的球的id
	int ballcanpullbc;//可以击打的球彩球否 -1为非snk
	int firsttochedballid;//第一次接触的球
	int haveredball;
	int downballidlst[22],downballidxlst[22],outballlst[22];
	int downballs,outballs;
	ZuoQiu()	{gameclear();};
	~ZuoQiu(){;};
public:
	void gameloop();
	void gameinputloop();
	void gameinit();
	void gameclear();
	void gamedestroy();
	void actmousebar()
	{
		if(gdata.gamesta!=GST_GAMING)return;
		if(!balltick.GetReady() || mousemode==0 || balltick.IsTracing())
		{
			gdata.mousebar=0;
			return;
		}
		gdata.mousebar=(gdata.mousebar==0)?1:0;
	}
	void initui()
	{

		m_smallwindlg.SetLocation(282,20);
		m_smallwindlg.SetSize(100,100);
		m_smallwindlg.SetCaptionHeight(10);
		m_smallwindlg.EnableCaption(true);
		//m_smallwindlg.SetCaptionText("'W' 2D/3D");
		
		m_helpdlg.SetLocation(13,16);
		m_helpdlg.SetSize(376,250);
		m_helpdlg.SetCaptionHeight(10);
		m_helpdlg.EnableCaption(true);
		//m_helpdlg.SetCaptionText("Help");
		m_helpdlg.SetVisible(false);

		m_configdlg.SetLocation(38,21);
		m_configdlg.SetSize(376-50,240);
		m_configdlg.SetCaptionHeight(10);
		m_configdlg.EnableCaption(true);
		m_configdlg.SetVisible(false);

		int xx=-15,yy=-25;
		for(int i=1;i<=9;i++)
			m_configdlg.RemoveControl(i);

		m_configdlg.AddSlider(1    ,154+xx,40+yy  ,100,10 ,  0,999,0);//fps
		m_configdlg.AddSlider(2    ,154+xx,70+yy   ,100,10 , 10,100,55);//time step
		m_configdlg.AddSlider(3    ,154+xx,100+yy  ,100,10 , 0,100,50);//e
		m_configdlg.AddSlider(4    ,154+xx,130+yy  ,100,10 , 0,100,50);//fricion
		m_configdlg.AddSlider(5    ,154+xx,160+yy  ,100,10 , 0,100,50);//impuls
		m_configdlg.AddCheckBox(6," ",51+xx,190+yy , 10,10);
		m_configdlg.AddButton(7,"  OK", 80+xx,230+yy , 50,20);
		m_configdlg.AddButton(8,"CANCEL", 230+xx,230+yy , 50,20);
		m_configdlg.AddSlider(9,    101+xx,210+yy, 50,8,   1,10000, 5000);
		
		UISlider* sl;
		sl=(UISlider*)m_configdlg.GetControl(1);//fps
		sl->SetValue(m_fps);
		sl=(UISlider*)m_configdlg.GetControl(2);//time step
		sl->SetValue(m_timstep*1000.0f);
		sl=(UISlider*)m_configdlg.GetControl(3);//e
		sl->SetValue(m_e*100.0f);
		sl=(UISlider*)m_configdlg.GetControl(4);//friction
		sl->SetValue(m_friction*100.0f);
		sl=(UISlider*)m_configdlg.GetControl(5);//impuls
		sl->SetValue(m_impulls*20.0f);

		sl=(UISlider*)m_configdlg.GetControl(9);//mouse
		sl->SetValue(m_mouserev*100.0f);
		
		UICheckBox *cb=(UICheckBox*)m_configdlg.GetControl(6);
		cb->SetChecked(m_bcheckstickcollid==0?false:true);

		m_configdlg.SetCallback(uicbproc,(void*)&gdata);
	}
	void MsgProcUI(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		if(gdata.gamesta==GST_GAMING)
			m_smallwindlg.MsgProc(hwnd,iMsg,wParam,lParam);
		else if(gdata.gamesta==GST_MENU)
			m_configdlg.MsgProc(hwnd,iMsg,wParam,lParam);
		//	m_helpdlg.MsgProc(hwnd,iMsg,wParam,lParam);
	};
	void renderui()
	{
		DWORD t=GetTickCount();
		POINT pt;float w,h;
		if(gdata.gamesta==GST_MENU)
		{
			if(!m_configdlg.GetVisible())return;
			m_configdlg.GetLocation(pt);
			w=m_configdlg.GetWidth();
			h=m_configdlg.GetHeight();

			FillLine(pt.x+1,pt.y+1+10, pt.x+w-1,pt.y+h+10,0);
			int xx=-27,yy=-30;
			print_string(45+xx  +pt.x   ,40 +17+yy+pt.y, 3, "GAME FPS  :");
			print_string(50+xx+pt.x+90  ,40+17+yy+pt.y,3,"+++");//fnum(  50+xx+90,40 +17+yy,1.0f,3,"%.1f");
			print_string(50+xx+pt.x+220 ,40+17+yy+pt.y,3,"---");//print_fnum(  50+xx+220,40 +17+yy,1.0f,3,"%.1f");

			print_string(45+xx+pt.x     ,70 +17+yy+pt.y, 3, "TIME STEP :");
			print_fnum(  50+xx+pt.x+90  ,70 +17+yy+pt.y, 0.1f,3,"%.1f");
			print_fnum(  50+xx+pt.x+220 ,70 +17+yy+pt.y, 1.0f,3,"%.1f");
			
			print_string(45+xx+pt.x    ,100+17+yy+pt.y, 3, "ELASTICITY:");
			print_fnum(  50+xx+pt.x+90 ,100 +17+yy+pt.y,0.0f,3,"%.1f");
			print_fnum(  50+xx+pt.x+220,100 +17+yy+pt.y,1.0f,3,"%.1f");
			
			print_string(45+xx+pt.x    ,130+17+yy+pt.y, 3, "FRICTION  :");
			print_fnum(  50+xx+pt.x+90 ,130 +17+yy+pt.y,0.0f,3,"%.1f");
			print_fnum(  50+xx+pt.x+220,130 +17+yy+pt.y,1.0f,3,"%.1f");
			
			print_string(45+xx+pt.x    ,160+17+yy+pt.y, 3, "IMPULLS   :");
			print_fnum(  50+xx+pt.x+90 ,160 +17+yy+pt.y,0.0f,3,"%.1f");
			print_fnum(  50+xx+pt.x+220,160 +17+yy+pt.y,5.0f,3,"%.1f");
			
			print_string(63+xx+pt.x   ,225+yy+pt.y,3  , "MOUSE:");


			print_fnum(  50+xx+pt.x+260  ,40 +17+yy+pt.y,m_fps,3,"%.0f");
			print_fnum(  50+xx+pt.x+260  ,70 +17+yy+pt.y,m_timstep,3,"%.2f");
			print_fnum(  50+xx+pt.x+260  ,100 +17+yy+pt.y,m_e,3,"%.2f");
			print_fnum(  50+xx+pt.x+260  ,130 +17+yy+pt.y,m_friction,3,"%.2f");
			print_fnum(  50+xx+pt.x+260  ,160 +17+yy+pt.y,m_impulls,3,"%.2f");
			print_fnum(  50+xx+pt.x+125  ,220 +7+yy+pt.y,m_mouserev,3,"%.2f");

			print_string(85+xx+pt.x,190+17+yy+pt.y, 3, "CHECK BALLSTICK COLLISION");

			m_configdlg.OnRender(t);
			return;
		}

		m_smallwindlg.OnRender(t);

		m_smallwindlg.GetLocation(pt);
		w=m_smallwindlg.GetWidth();
		h=m_smallwindlg.GetHeight();
		print_string(pt.x+2,pt.y+2,57, "<W>2D/3D");
		if(!m_smallwindlg.GetMinimized())
		{
			FillLine(pt.x+1,pt.y+10+1, pt.x+w-1, pt.y+10+h,0);
			
			Camera *cm=RDev.SysCamera;
			static int smcammd=0;
			if(getkey('W',true))
				smcammd=(smcammd==0)?1:0;
			if(smcammd==0)
				RDev.SysCamera=&smallcam2d;
			
			RDev.SetViewPortEx(Vector3(pt.x,pt.y+10,0),90,w,h,w);
			balldesk.DrawDesk();
			drawballs(true);
			RDev.SysCamera=cm;
			RDev.SetViewPortEx(Vector3(6,6,0),90,WIDTH,HEIGHT,WIDTH);
			SetClipRect(7,13,WIDTH-12,HEIGHT-33);
		}
		if(m_helpdlg.GetVisible())
		{	m_helpdlg.OnRender(t);
			POINT pt;m_helpdlg.GetLocation(pt);
			int sw=m_helpdlg.GetWidth(),sh=m_helpdlg.GetHeight();
			int sx=pt.x,sy=pt.y;
			FillLine(sx+1,sy+1,sx+sw,sy+10,0);
			FillLine(sx+1,sy+10+1,sx+sw,sy+sh+10,0);
			sx+=2;sy+=20;
			print_string(sx,sy,57,	  "<F2/F3> <2/3>:  2D/3D");
			print_string(sx,sy+20,57, "<CTRL>       :  CONTROL BALL STICK, ENTER GAME");
			print_string(sx,sy+40,57, "<4> <5>      :  STICK CONTROL MODE ");
			print_string(sx,sy+60,57, "<Z/A>        :  CAMERA HIGH");
			print_string(sx,sy+80,57, "<C>          :  CAMERA TRACE");
			print_string(sx,sy+100,57,"<SPACE>      :  SHOW BALL ID");
			print_string(sx,sy+120,57,"<T>          :  SHOW TIP LINE ");
			print_string(sx,sy+140,57,"<SHIFT>      :  PRISICE CONTROL");
			print_string(sx,sy+160,57,"<ENTER>      :  ENTER GAME");
			print_string(sx,sy+180,57,"<UP/DOWN/LEFT/RIGHT>: MOVE CAMERA");
			print_string(sx+220,sy+220,57,"DESGINER: BJASON");
		}
		
	}
	void SetCamMode(int d)//设置显示模式，显示模式也决定操作方式
	{
		cammode=d;
		balltick.SetCamMode(d);
		if(gdata.gametyp==GTP_AM9)
		{
			maincam.LookAt(Point3(0,-240,-250),Vector3(0,1,1),Vector3(0,1,0));
			cam2d.LookAt(Point3(-6,-280,-4),Vector3(0,1,0),Vector3(-1,0,0));
			smallcam2d.LookAt(Point3(-6,-280,-4),Vector3(0,1,0),Vector3(-1,0,0));
		}
		else if(gdata.gametyp==GTP_LUODAI8)
		{
			maincam.LookAt(Point3(0,-240,-250),Vector3(0,1,1),Vector3(0,1,0));
			cam2d.LookAt(Point3(-6,-280,-4),Vector3(0,1,0),Vector3(-1,0,0));
			smallcam2d.LookAt(Point3(-6,-280,-4),Vector3(0,1,0),Vector3(-1,0,0));
		}
		else if(gdata.gametyp==GTP_SNK)
		{
			maincam.LookAt(Point3(0,-350,-350),Vector3(0,1,1),Vector3(0,1,0));
			cam2d.LookAt(Point3(-9,-380,-4),Vector3(0,1,0),Vector3(-1,0,0));
			smallcam2d.LookAt(Point3(-9,-380,-4),Vector3(0,1,0),Vector3(-1,0,0));
		}
		if(cammode==2)//2d
			RDev.SetCamera(&cam2d);
		else if(cammode==3)//3d
			RDev.SetCamera(&maincam);	
	}
	void saveturn()
	{
		if(turnsaved==1)return;
		for(int i=0;i<currballs;i++)
			bkball[i]=ball[i];
		bkballtick=balltick;
		turnsaved=1;
	}
	void loadturn()
	{
		if(turnsaved==0)return;
		for(int i=0;i<currballs;i++)
			ball[i]=bkball[i];
		balltick=bkballtick;
		turnsaved=0;
	}
	void drawpickball()
	{
		if(bmouse==false)return;
		int pickb=-1;Vector3 ins;
		RayT rt=RDev.GetMouseVec(mx,my);
		if(lmclked==false && pickspc==0)
		{
#ifdef _TEST
			for(int i=0;i<2;i++)
#else
			for(int i=0;i<currballs;i++)
#endif
			{	
				if(balllst[i]->enable==false)continue;
				if(balllst[i]->bjind==true)continue;
				if(GetInsectLS(rt.start,rt.end,balllst[i]->_pos,BALLR,ins))
				{
					pickb=i;
					break;
				}
			}
			if(pickb!=-1)
			{
				balllst[pickb]->DrawCir();
				pickedball=balllst[pickb];
			}
			else pickedball=NULL;
		}
		else if(lmclked==true || pickspc==1)
		{
			if(pickedball==NULL)return;
			if(trainmode==0){if(pickmode==0)return;}
			if(GetInsectInTri(rt.start,rt.end,balldesk.p[0],balldesk.p[1],balldesk.p[3],ins))
			{
				float ww=balldesk.actw-BALLR;
				float hh=balldesk.acth-BALLR;
				float h1,h2;h1=-hh;h2=hh;
				if(trainmode==0)//正式模式
				{
					if(gdata.gametyp==GTP_SNK)
					{
						if(pickedball->id!=0)return; //不是白球不能移动
						h1=-hh;
						h2=-0.6f*balldesk.acth;
					}
					if(pickedball->id==0)
						balltick.ball0=pickedball->_pos;
				}
				if(ins.x<-ww)	ins.x=-ww;
				else if(ins.x>ww)ins.x=ww;
				if(ins.z<h1)	ins.z=h1;
				else if(ins.z>h2)ins.z=h2;
#ifdef _TEST
				for(int i=0;i<2;i++)
#else
				for(int i=0;i<currballs;i++)
#endif
				{
					if(ball[i].enable==false)continue;
					if(ball[i].bjind==true)continue;
					if(&ball[i]==pickedball)continue;
					Vector3 v=ins-ball[i]._pos;
					v.y=0;
					if(v*v<SQR(BALLR+BALLR))
					{
						return;
						//v.Unit();
						//ins=ball[i]._pos+v*(BALLR+BALLR);
						//break;
					}
				}
				pickedball->_pos=Vector3(ins.x,-BALLR,ins.z);
				pickedball->_vel=Vector3(0,0,0);
				pickedball->_angvel=Vector3(0,0,0);
				if(pickspc==1)
				{
					if(lmclked)
					{
						pickspc=0;
						pickedball=NULL;
					}
				}
			}
		}
	};
	void AddToPhyWorld()
	{
		int i;
		int lmp[18]={0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0};
		for(i=0;i<18;i++)
		{
			if(lmp[i]==0)
			{
				balldesk.m_rect[i].e=gdata.e*0.1f;//0.01f;
				balldesk.m_rect[i].friction=gdata.friction*0.05f;//0.2f;
			}
			else
			{
				balldesk.m_rect[0].e=gdata.e;//0.7f;
				balldesk.m_rect[0].friction=gdata.friction*0.05f;//0.1f;
			}
//			m_world.Add(&balldesk.m_rect[i]);//已改为自动碰撞
		}

		balldesk.m_rects.e=gdata.e;
		balldesk.m_rects.friction=gdata.friction;
		m_world.Add(&balldesk.m_rects);

		balldesk.m_hull.e=gdata.e*0.1f;
		balldesk.m_hull.friction=gdata.friction;//0.8f;
		m_world.Add(&balldesk.m_hull);
		for(i=0;i<6;i++)
		{
			balldesk.m_cir[i].e=gdata.e*0.1f;//0;
			balldesk.m_cir[i].friction=gdata.friction*0.1f;//0.1f;
			m_world.Add(&balldesk.m_cir[i]);
		}
//		m_world.Add(&balldesk.m_dsk);
#ifdef _TEST
		for(i=0;i<2;i++)
#else
		for(i=0;i<currballs;i++)
#endif
		{
			ball[i].bjind=false;
			ball[i].bout=false;
			ball[i]._vel=Vector3(0,0,0);
			ball[i]._angvel=Vector3(0,0,0);
			ball[i]._quat=Quat();
			ball[i].e=0.98f;
			ball[i].friction=0.04f;
			ball[i].enable=true;
			m_world.Add(&ball[i]);
		}
	};
	void setgamemode(GAMETYP gtp)
	{
		balldesk.SetDesk(gtp);
		placeball(gtp);
		balltick.init();
		balltick.SetTick(gtp);
		balltick.Create(ball,&balldesk,&gdata);
		AddToPhyWorld();
		if(gtp==GTP_AM9)
			SetCamMode(3);
		else SetCamMode(2);
		getcurrball();//获得当前可打球//规则初始化
		entergame();
	}
	//game logic
	void changeplayer()
	{
		if(gdata.gameplayers==1)
			gdata.currplayer=(gdata.currplayer==0)?1:0;
	};
	void changamesta(GAMESTA sta)
	{
		gdata.oldsta=gdata.gamesta;
		gdata.gamesta=sta;
		switch(gdata.gamesta)
		{
		case GST_GAMEEND:
		case GST_XUMU:
			{
				ShowCur();
			}
			break;

		}
	};
	void drawstartmenu();
	void drawxumu()
	{
		int tm=(gettimetick()/700)%2;
		print_string(127,240,tm*2,"Press Enter to skip",0);

		m_xumuwd.Step(gdata.timstep);
		Line_(xumurect.position.x-80,xumurect.position.y, xumurect.position.x+72,xumurect.position.y+5,57,true);
		for(int i=0;i<7;i++)
			Circle(xumuball[i].position.x,xumuball[i].position.y,xumuball[i].rad,57);
		char tt[7]={'S','N','O','O','K','E','R'};
		for(i=0;i<7;i++)
		{
			Vector2 v=xumuball[i].position-Vector2(130+i*22,105);v.Unit();v=-v*xumuball[0].rad;
			line(130+i*22,105,   xumuball[i].position.x+v.x,xumuball[i].position.y+v.y,57);
			print_char(xumuball[i].position.x-3,xumuball[i].position.y-3,tt[i],57);
		}

	};
	void drawpausemenu()
	{
		print_string(130,100,2,"Pause",2);
	}
	void drawbkground()
	{
		print_string(6,2,57,"BinfenSoft Studio(C)");
		Line_(6,12,394,294,57,true);
	};
	void drawscr()
	{
		Line_(7,280, WIDTH-7,280, 57);
		print_string(7+2,280+4, 57, "1P");

		print_string(34,284, 57, "0000");
//		if(gdata.gameplayers==1)
			print_string(7+100,284, 57, "2P");
			print_string(133,284, 57, "0000");

		if(getkey('U',true))gdata.currplayer=!gdata.currplayer;
		Vector2 ps;
		if(gdata.currplayer==0)
		{
			ps=Vector2(28,287);
		}
		else 
		{
			ps=Vector2(126,287);
		}
		int tm=(GetTickCount()/600)%2;

		if(ballcanpullid>=0)
		{
			int c=57;
			if(gdata.gametyp==GTP_SNK)c=ball[ballcanpullid].c;
			else c=ball[ballcanpullid].c;
			if(!pickmode)
				FillCircle(ps.x,ps.y,2,tm*c);
			else Circle(ps.x,ps.y,tm+1,c);
		}		
		//if(getkey('J',true))
			//Eft.startdoscr(10);
		if(getkey('K',true))
			pickmode=!pickmode;

		if(balltick.getopr()==0)
		{
			if(!mousemode)
			{
				if(trainmode)	print_string(253,284,57,"TRAIN MODE");
				else print_string(253,284, 57,"<F1> HELP");
			}
			else print_string(288,284, 57,"MOUSE");
		}
		else 
		{
			print_string(253,284, 57,"AUTO");
			if(mousemode)print_string(288,284, 57,"MOUSE");
		}
	}
	void drawballs(bool sp=false)
	{
		Vector3 bj,bj1;
		int j,p,h;_ball *t;
#ifdef _TEST
		for(h=1;h>0;h=p)
#else
		for(h=currballs-1;h>0;h=p)
#endif
		{
			for(p=j=0;j<h;j++)
			{
				bj=balllst[j]->_pos*RDev.SysCamera->ViewMat;
				bj1=balllst[j+1]->_pos*RDev.SysCamera->ViewMat;
				if(bj.z>bj1.z)
				{
					t=balllst[j];
					balllst[j]=balllst[j+1];
					balllst[j+1]=t;
					p=j;
				}
			}
		}
#ifdef _TEST
		for(int i=1;i>=0;i--)
#else 
		for(int i=currballs-1;i>=0;i--)
#endif
			balllst[i]->DrawBall(sp);
		if(balltick.bready==true)
			ball[0].DrawTipprim();
	}
	void placeball(GAMETYP gtp)
	{
		float r=BALLR+0.1f;
		int i,j=0;
		float ix,iy;
		float sin60=sin(60*Pi),cos60=cos(60*Pi);
		Vector3 p[22],px,py;
		int *tbl=NULL;
		switch(gtp)
		{
		case GTP_AM9:
			{
				tbl=ball_us9tbl;
				px=Vector3(cos60,0,sin60);
				py=Vector3(cos60,0,-sin60);
				p[j++]=Vector3(0,0,-2.0f/3.0f*balldesk.acth);
				for(iy=0;iy<3;iy++)
				{
					for(ix=0;ix<3;ix++)
					{
						p[j]=ix*px+iy*py;
						p[j]=p[j]*(2*r)+Vector3(-2*r,0,0)+Vector3(0,0,1.0f/2.0f*balldesk.acth);
						j++;
					}
				}
			}
			break;
		case GTP_LUODAI8:
			{
				tbl=ball_ld8tbl;
				px=Vector3(1,0,0);
				py=Vector3(cos60,0,-sin60);
				p[j++]=Vector3(0,0,-2.0f/3.0f*balldesk.acth);
				for(iy=0;iy<5;iy++)
				{
					for(ix=0;ix<5-iy;ix++)
					{
						p[j]=ix*px+iy*py;
						p[j]=p[j]*(2*r)+Vector3(-4*r,0,r*cos60)+Vector3(0,0,1.0f/2.0f*balldesk.acth);
						j++;
					}
				}
			}
			break;
		case GTP_SNK:
			{
				Vector3 o=Vector3(0,0,0.6f*balldesk.acth);
				px=Vector3(1,0,0);
				py=Vector3(cos60,0,-sin60);
				p[j++]=Vector3(0,0,-0.6f*balldesk.acth-8*r);
				for(iy=0;iy<5;iy++)
				{
					for(ix=0;ix<5-iy;ix++)
					{
						p[j]=ix*px+iy*py;
						p[j]=p[j]*(2*r)+Vector3(-4*r,0,r*cos60)+o;
						j++;
					}
				}
				p[j++]=Vector3(8*r,0,-0.6f*balldesk.acth);//黄
				p[j++]=Vector3(-8*r,0,-0.6f*balldesk.acth);//绿
				p[j++]=Vector3(0,0,-0.6f*balldesk.acth);//棕
				p[j++]=Vector3(0,0,0);//兰
				p[j++]=Vector3(0,0,-4*r/sin60-4*r)+o;//粉
				p[j++]=Vector3(0,0,6*r)+o;//黑

				ball[0].SetSnkID(0,0);
				for(i=1;i<16;i++)
					ball[i].SetSnkID(1,i);
				ball[16].SetSnkID(2,16);
				ball[17].SetSnkID(3,17);
				ball[18].SetSnkID(4,18);
				ball[19].SetSnkID(5,19);
				ball[20].SetSnkID(6,20);
				ball[21].SetSnkID(7,21);
				for(i=0;i<j;i++)
					ball[i]._pos=p[i]+Vector3(0,-BALLR,0);
#ifdef _TEST
				for(i=0;i<2;i++)
#else
				for(i=0;i<j;i++)
#endif
				{
					balllst[i]=&ball[i];
				}
				currballs=j;
			}
			break;
		}
		if(tbl==NULL)return;
		for(i=0;i<j;i++)
		{
			ball[i].SetID(tbl[i],i);
			ball[i]._pos=p[i]+Vector3(0,-BALLR,0);
		}
#ifdef _TEST
		for(i=0;i<2;i++)
#else 
		for(i=0;i<j;i++)
#endif
		{
			balllst[i]=&ball[i];
		}
		currballs=j;
	};
	void dojindong(_ball *bl)
	{
		downballidlst[downballs]=bl->id;
		downballidxlst[downballs]=bl->idx;
		downballs++;
		if(gdata.gametyp==GTP_SNK)
		{
			if(haveredball)
			{
				bool bhave=false;
				for(int i=0;i<currballs;i++)
					if(ball[i].bjind==false && ball[i].id==1)
					{
						bhave=true;
						haveredball=1;break;
					}
				if(!bhave)haveredball=0;
			}
		}
	};
	void getcurrball()//当前规则下可打得球
	{
		int minb=30,mini=0;
		if(gdata.gametyp==GTP_SNK)
		{
			if(haveredball==0)
			{
				for(int i=1;i<currballs;i++)
				{
					if(!ball[i].bjind && minb>ball[i].id)
					{
						minb=ball[i].id;
						mini=i;
					}
				}
				ballcanpullbc=1;
			}
		}
		else if(gdata.gametyp==GTP_LUODAI8)
		{
			int bc=(gdata.currplayer==0)?-1:1;
			for(int i=1;i<currballs;i++)
			{
				int cc=((ball[i].id<=8)?-1:1)*bc;
				if(!ball[i].bjind && (cc>0) && minb>ball[i].id)
				{
					minb=ball[i].id;
					mini=i;
				}
			}
		}
		else if(gdata.gametyp==GTP_AM9)
		{
			for(int i=1;i<currballs;i++)
			{
				if(!ball[i].bjind && minb>ball[i].id)
				{
					minb=ball[i].id;
					mini=i;
				}
			}
		}
		ballcanpullid=mini;
	}
	int checkcanbready()//0: not ready, 1: ready, 2:over
	{
		int ret=1,over=1,i;
		for(i=0;i<currballs;i++)
		{
			if(ball[i].bjind==false)
			{
				over=0;
			}
			else continue;
			if(ball[i].v!=0)
			{
				ret=0;
				break;
			}

		}
		if(over)return 2;
		else return ret;
	}
	void clearturn()
	{
		memset(downballidlst,0,sizeof(int)*22);
		memset(outballlst,0,sizeof(int)*22);
		memset(downballidxlst,0,sizeof(int)*22);
		downballs=0;
		outballs=0;
		turnsaved=0;
	}
	int getbc(int id)//是否花色或单色 0 单色，1 花色 -1 am9球
	{
		if(gdata.gametyp==GTP_SNK)
		{
			if(id>=16)return 1;
			else return 0;
		}
		else if(gdata.gametyp==GTP_LUODAI8)
		{
			if(id>0&&id<=8)return 0;
			else if(id>8 && id<=15) return 1;
		}
		return -1;
	}
	void checkallrulsandrespos()//在击球后所有球停止时判断
	{
		int ret=checkcanbready();
		if(ret==1)//停球后
		{
			if(balltick.GetReady())
			{
				if(!balltick.IsTracing())
				{
					saveturn();//第一次和loadturn后才save，多则无效果
				}
			}
			else
			{
				if(outballs)
				{
					loadturn();
					clearturn();
					return;
				}
				//ruls
				bool rightball=false,whiteballdown=false,end16=false,end9=false,samebc=false;
				for(int i=0;i<downballs;i++)
				{
					if(downballidlst[i]==0)	whiteballdown=true;
					else if(downballidlst[i]==ballcanpullid)
						rightball=true;
					if( getbc(downballidlst[i])==ballcanpullbc )
						samebc=true;
					if(downballidlst[i]==8 || (currballs-downballs)==0)
						end16=true;
					else if(downballidlst[i]==9 || (currballs-downballs)==0)
						end9=true;
					if(gdata.gametyp==GTP_SNK)
					{
						if( getbc(downballidlst[i]) ==1)
							ball[downballidxlst[i]].reset();
					}
				}
				if(gdata.gametyp==GTP_SNK)
				{
					if(whiteballdown)//进白球
					{
						changeplayer();
					}
					if(downballs && !rightball && !samebc)
					{
						
					}
				}
				else if(gdata.gametyp==GTP_AM9)
				{
					if(!downballs)changeplayer();
					else if(whiteballdown)
					{
						ball[0].reset();
						pickmode=1;
						ShowCur();
						changeplayer();
					}
					else if(!rightball)changeplayer();
					if(end9)changamesta(GST_GAMEEND);
					
				}
				else if(gdata.gametyp==GTP_LUODAI8)
				{
					if(!downballs)changeplayer();
					else if(whiteballdown)
					{
						ball[0].reset();
						pickmode=1;
						ShowCur();
						changeplayer();
					}
					if(end16)changamesta(GST_GAMEEND);
				}
				getcurrball();
				clearturn();
				balltick.SetReady();
			}
		}
		else if(ret==2){;};//over
	}
	void stopallballs()
	{
		for(int i=0;i<currballs;i++)
			ball[i].clearmove();
	}
	void entergame()
	{
		if(pickmode==1)
			pickmode=0;
		HideCur();
	}
	void drawscene();

};
int _SphereRectsColid( Contact *contacts, Body* bodyA, Body* bodyB)
{
	_ball * bl=(_ball*)bodyA;
	ZuoQiu *zq=(ZuoQiu*)(bl->gdt->zuoqiu);
	Contact ct;
	int cts,maxsep=-100,cs=0;
	for(int i=0;i<18;i++)
	{
		cts=_SphereRectColid(&ct,bodyA,&(zq->balldesk.m_rect[i]));
		if(cts)
		{
			if(maxsep<ct.separation)
			{
				maxsep=ct.separation;
				bodyB->e=zq->balldesk.m_rect[i].e;
				bodyB->friction=zq->balldesk.m_rect[i].friction;
				*contacts=ct;
			}
			cs=1;
		}
	}
	return cs;
}
int MyColidfunc( Contact *contacts, Body* bodyA, Body* bodyB)
{
	int cts=0;
	
	if(bodyA->shapetype==S_SPHERE && bodyB->shapetype==S_SPHERE)
	{
		cts=_SphereSphereColid(contacts,bodyA,bodyB);
		_ball *a=(_ball*)bodyA;
		_ball *b=(_ball*)bodyB;
		ZuoQiu *zq=(ZuoQiu*)a->gdt->zuoqiu;
		if(zq->firsttochedballid==-1)
		{
			if(a->id==0)
			{
				zq->firsttochedballid=b->id;
			}
			if(b->id==0)
			{
				zq->firsttochedballid=a->id;
			}
		}
	}
	else if(bodyA->shapetype==S_SPHERE && bodyB->shapetype==S_RECT)
		cts=_SphereRectColid(contacts,bodyA,bodyB);
	else if(bodyA->shapetype==S_RECT && bodyB->shapetype==S_SPHERE)
		cts=_SphereRectColid(contacts,bodyB,bodyA);
	else if(bodyA->shapetype==S_SPHERE && bodyB->shapetype==S_HULLPLAN)
		cts=_SphereHullColid(contacts,bodyA,bodyB);
	else if(bodyA->shapetype==S_HULLPLAN && bodyB->shapetype==S_SPHERE)
		cts=_SphereHullColid(contacts,bodyB,bodyA);
	else if(bodyA->shapetype==S_SPHERE && bodyB->shapetype==S_ARCSYLIND)
		cts=_SphereArcSydColid(contacts,bodyA,bodyB);
	else if(bodyA->shapetype==S_ARCSYLIND && bodyB->shapetype==S_SPHERE)
		cts=_SphereArcSydColid(contacts,bodyB,bodyA);
	else if(bodyA->shapetype==S_SPHERE && bodyB->shapetype==S_OTHER+1)
		cts=_SphereRectsColid(contacts,bodyA,bodyB);
	else if(bodyA->shapetype==S_OTHER+1 && bodyB->shapetype==S_SPHERE)
		cts=_SphereRectsColid(contacts,bodyB,bodyA);
		
		return cts;
}
void _ball::reset()
{
	ZuoQiu *zq=(ZuoQiu*)(gdt->zuoqiu);		
	float acth=zq->balldesk.acth,sin60=sin(60*Pi),r=BALLR;
	Vector3 o=Vector3(0,0,0.6f*acth);
	bjind=false;
	enable=true;
	_quat=Quat();
	_angvel=Vector3(0,0,0);
	_vel=Vector3(0,0,0);
	if(id==0)
	{
		_pos=Vector3(0,-r,-0.6f*acth-4*r);
		zq->pickspc=1;
		zq->pickedball=this;
		return;
	}
	if(bc==1)//彩球
	{
		if(id==16)_pos=Vector3(8*r,-r,-0.6f*acth);//黄
		else if(id==17)_pos=Vector3(-8*r,-r,-0.6f*acth);//绿
		else if(id==18)_pos=Vector3(0,-r,-0.6f*acth);//棕
		else if(id==19)_pos=Vector3(0,-r,0);//兰
		else if(id==20)_pos=Vector3(0,-r,-4*r/sin60-4*r)+o;//粉
		else if(id==21)_pos=Vector3(0,-r,6*r)+o;//黑
	}
}
void _ball::calc()
{
	ZuoQiu *zq=(ZuoQiu*)(gdt->zuoqiu);
	if(_pos.y>BALLR && bjind==false)
	{
		bjind=true;
		zq->dojindong(this);
		_vel=Vector3(0,0,0);
		_angvel=Vector3(0,0,0);
		_pos=Vector3(0,0,0);
		enable=false;
		return;
	}
	if(bjind==true)return;
	float ww=zq->balldesk.dskw+zq->balldesk.tr;
	float hh=zq->balldesk.dskh+zq->balldesk.tr;
	if(_pos.x<-ww || _pos.x>ww || _pos.z<-hh || _pos.z>hh)
	{
		if(bout==false)
		{
			bout=true;
			zq->outballlst[zq->outballs++]=id;
		}
	}
	v=_vel.Mod();
	if(ABS(v)<0.5f)
	{
		v=0;
		_vel=Vector3(0,0,0);
		_angvel=Vector3(0,0,0);
	}
}
void GameEffect::startdoscr(int sc)
{
	Eftstr *estr=new Eftstr;
	if(estr==NULL){fals+=1;return;};
	news+=1;
	estr->Eftp=EFT_SCR;
	estr->dtime=gettimetick();
	estr->lagtime=0;
	estr->scr=sc;
	ZuoQiu *zq=(ZuoQiu*)(gdt->zuoqiu);
	if(gdt->currplayer==0)	estr->ps[0]=Vector2(38,282);
	else estr->ps[0]=Vector2(136,282);
	
	Eftlst.Push(estr);
};
bool GameEffect::loopdoscr(Eftstr *eft)
{
	unsigned int dtime=gettimetick()-eft->dtime;
	if(eft->lagtime)
	{ if(((dtime/1000) <eft->lagtime ))return true;
	else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
	}
	int alp= (dtime/100);
	if(alp>10)return false;
	float sh=12.0f/10.0f;
	float y=sh*(float)alp;

	Vector2 ps=eft->ps[0]+Vector2(0,-y);
	if(eft->scr<0)
	{
		print_char(ps.x-5,ps.y,'-',15,1);
		print_num(ps.x,ps.y,ABS(eft->scr),15,1);
	}
	else
	{
		print_char(ps.x-5,ps.y,'+',36,1);
		print_num(ps.x,ps.y,ABS(eft->scr),36,1);
	}

	return true;
};
void ZuoQiu::gameloop()
{
	GAMESTA gst=gdata.gamesta;
	switch(gst)
	{
	case GST_XUMU:
		drawbkground();
		drawxumu();
		break;
	case GST_MENU:
		drawbkground();
		drawstartmenu();
		renderui();
		break;
	case GST_GAMEEND:
		{
			drawbkground();
			drawscr();
			balldesk.DrawDesk();
			float ic=(GetTickCount()/100)%360;
			Vector3 cp=Vector3(cos(ic*Pi),-1,sin(ic*Pi))*200;
			RDev.SysCamera->LookAt(cp,-cp,Vector3(0,1,0));
		}
		break;
	case GST_GAMING:
		{
			drawbkground();
			drawscr();
			drawscene();
			m_world._Step(gdata.timstep);
			for(int i=0;i<currballs;i++)
				ball[i].calc();
			if(getkey('P',true))stopallballs();
			//if(getkey('H'))ball[0]._pos+=Vector3(0,-10,0);
			checkallrulsandrespos();
			Eft.Effectloop();
		}
		break;
	case GST_PAUSE:
		drawbkground();
		drawpausemenu();
		break;
	case GST_CONTINUE:
		{
			drawbkground();
			print_string(130,150,2,"CONTINUE GAME? Y/N");
		}
		break;
	}
}
void ZuoQiu::gameinputloop()
{
	GAMESTA gst=gdata.gamesta;
	switch(gst)
	{
	case GST_XUMU:
		{
			if(getkey(VK_SPACE,true)||getkey(VK_RETURN,true))
				changamesta(GST_MENU);
		}
		break;
	case GST_MENU:
		{
			if(m_configdlg.GetVisible())break;
			if(getkey(VK_ESCAPE,true))changamesta(GST_XUMU);
			if(getkey(VK_UP,true))
			{
				mnuidx-=1;if(mnuidx<0)mnuidx=3;
			}
			else if(getkey(VK_DOWN,true))
			{
				mnuidx+=1;if(mnuidx>3)mnuidx=0;
			}
			if(mnuidx==2)
			{
				if(getkey(VK_RETURN,true))
				{
					mnuidx1+=1;
					if(mnuidx1>3)mnuidx1=0;
					trainmode=0;
					if(mnuidx1==0)			gdata.gametyp==GTP_AM9;
					else if(mnuidx1==1)		gdata.gametyp=GTP_LUODAI8;
					else if(mnuidx1==2)		gdata.gametyp=GTP_SNK;
					else if(mnuidx1==3){
						trainmode=1;
						gdata.gametyp=GTP_AM9;
					}

				}
			}
			else if(mnuidx==3)
			{
				if(getkey(VK_RETURN,true))
				{
					m_configdlg.SetVisible(!m_configdlg.GetVisible());
				}
			}
			else if(mnuidx==0||mnuidx==1)
			{
				if(getkey(VK_RETURN,true))
				{
					gdata.gameplayers=mnuidx;
					changamesta(GST_GAMING);
					setgamemode(gdata.gametyp);
				}
			}
		}
		break;
	case GST_GAMEEND:
		{
			if(getkey(VK_ESCAPE,true))
			{
				changamesta(GST_CONTINUE);
			}
		};
		break;
	case GST_GAMING:
		{
			RDev.SysCamera->TransefCameraByKey(false);
			if(getkey(VK_F2,true) || getkey('2',true) )
				SetCamMode(2);
			if(getkey(VK_F3,true) || getkey('3',true) )
				SetCamMode(3);
			if(getkey('5',true))
				mousemode= (mousemode==0?1:0);
			//if(getkey('1',true))SetCamMode(1);
			
			if(bmouse)
			{
				if(getkey(VK_RETURN,true)) entergame();
				else if(getkey(VK_CONTROL,true)) entergame();
				if(getkey(VK_ESCAPE,true))
				{
					changamesta(GST_CONTINUE);
				}
			}
			else 
			{
				if(getkey(VK_ESCAPE,true))
					ShowCur();

			}
		}
		break;
	case GST_CONTINUE:
		{
			if(getkey('Y',true)||getkey(VK_ESCAPE,true))
			{
				changamesta(gdata.oldsta);
				//changamesta(GST_GAMING);
			}
			else if(getkey('N',true))
			{
				changamesta(GST_XUMU);
				gameclear();
			}
		}
		break;
	}

	if(ActiveApp && false==bmouse)
	{
		POINT pt={WIDTH*0.5f,HEIGHT*0.5f};
		ClientToScreen(hWnd,&pt);
		SetCursorPos(pt.x,pt.y);
		
	}
}
void ZuoQiu::gameclear()
{
	mousemode=0;
	ballcanpullbc=-1;
	ballcanpullid=0;
	haveredball=1;
	firsttochedballid=-1;
	turnsaved=0;
	trainmode=0;
	pickmode=0;pickspc=0;
	pickedball=NULL;
	currballs=0;
	mnuidx=0;
	cammode=2;
	m_world=World(Vector3(0,9.8f,0),10);
	m_xumuwd=World(Vector2(0,9.8f),10);
	gdata=_gdata((void*)this);

	//gdata.init();
	for(int i=0;i<22;i++)
		ball[i].SetGdt(&gdata);
	Eft.SetGdt(&gdata);
	Eft.SetPdt(pdt);
	gameinit();

	mnuidx=mnuidx1=0;
	gdata.gametyp=GTP_AM9;
	clearturn();

}


void ZuoQiu::drawstartmenu()
{
	int tx=100,ty=100;
	print_string(tx+30,ty+50,2,"---Game Start---",0);
	print_string(tx+60,ty+70,2,"Single");
	print_string(tx+60,ty+90,2,"Mutiple");
	print_string(tx+30,ty+110,2,"---Game Option---");
	print_string(tx+60,ty+130,2,"Mode");
	print_string(tx+60,ty+150,2, "Config");

	char ch[16];memset(ch,0,sizeof(char)*16);
	if(trainmode==1)strcpy(ch,"TRAIN");
	else if(gdata.gametyp==GTP_AM9)strcpy(ch,"US9");
	else if(gdata.gametyp==GTP_LUODAI8)strcpy(ch,"US16");
	else if(gdata.gametyp==GTP_SNK)strcpy(ch,"SNK");

	int sy=mnuidx*20;
	if(mnuidx>1)sy+=20;

	print_string(tx+100,ty+130,2,ch);
	print_string(tx+50,ty+70+sy,2,"*");
	
}





void ZuoQiu::gameinit()
{
	char ct=1;
	lineclr(255,255,0  , 0,0,0,  ct+0*7, ct+1*7);//黄
	lineclr(0  ,0  ,255, 0,0,0,  ct+1*7, ct+2*7);//兰
	lineclr(255,0  ,0  , 0,0,0,  ct+2*7, ct+3*7);//红
	lineclr(140 ,0 ,140, 0,0,0,  ct+3*7, ct+4*7);//紫
	lineclr(255,128,200, 0,0,0,  ct+4*7, ct+5*7);//粉  
	lineclr(0  ,255,0  , 0,0,0,  ct+5*7, ct+6*7);//绿
	lineclr(158,50,0, 0,0,0,  ct+6*7, ct+7*7);//棕
	lineclr(100,100,100, 0,0,0,  ct+7*7, ct+8*7);//黑
	lineclr(255,250,200, 0,0,0,  ct+8*7, ct+9*7);//白

	//////////////////////////////////////////////////////
	DefInit3D();
	RDev.SetViewPort(Vector3(6,6,0),WIDTH,HEIGHT,WIDTH);
	SetClipRect(7,13,WIDTH-12,HEIGHT-33);
	
	m_world.Clear();
	m_world.SetColidFunc(MyColidfunc);
	
	m_xumuwd.Clear();

	xumurect.SetRect(Vector2(160,2),FLT_MAX);
	xumurect.position=Vector2(200,100);

	m_xumuwd.Add(&xumurect);
	xumuball[0].SetSphere(10,20);
	xumuball[0].e=0.95f;
	xumuball[0].position=Vector2(130,100)+ Vector2(-70,0);
	xumujt[0].SetBall(&xumuball[0],&xumurect, Vector2(130,100));
	m_xumuwd.Add(&xumuball[0]);
	m_xumuwd.Add(&xumujt[0]);
	
	for(int i=1;i<7;i++)
	{
		xumuball[i].SetSphere(10,20);
		xumuball[i].position=Vector2(130+i*22,170);
		xumuball[i].e=0.95f;
		xumujt[i].SetBall(&xumuball[i],&xumurect, Vector2(130+i*22,100));
		m_xumuwd.Add(&xumuball[i]);
		m_xumuwd.Add(&xumujt[i]);
	}


	initui();
	changamesta(GST_XUMU);

	maincam.init(90,WIDTH,HEIGHT,WIDTH);
	cam2d.init(90,WIDTH,HEIGHT,WIDTH);
	for(i=0;i<6;i++)
		smallcam[i].init(90,m_smallwindlg.GetWidth(),m_smallwindlg.GetHeight(),m_smallwindlg.GetWidth());
	smallcam2d.init(90,m_smallwindlg.GetWidth(),m_smallwindlg.GetHeight(),m_smallwindlg.GetWidth());

	SetCamMode(2);
	balltick.init();
	Eft.Effectdestroy();
	m_configdlg.SetVisible(false);
	m_helpdlg.SetVisible(false);
	m_smallwindlg.SetMinimized(false);
}

void ZuoQiu::drawscene()
{
	balldesk.DrawDesk();
	drawballs();
	if(pickmode==0)
	{
		balltick.drawtick();
		balltick.drawspeedbar();
		balltick.drawballtip();
	}	
	drawpickball();
	renderui();
}

ZuoQiu zuoqiu;
static INT64 _speed=0,_fps=1000;
static int mmkeys=10,mmgams=0;

void DoFrame();
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR szCmdLine, int iCmdShow)
{
	MSG	msg;
	
	if(!_m_buf.InitWindow(WIDTH, HEIGHT, "GEngin  -  ZuoQiu", hInstance, &hWnd, WndProc, NULL)) return FALSE;
	if(!_m_buf.SetBufferMode(WIDTH, HEIGHT, BPP, FullScreen, &tcf)) return FALSE;

	m_e=zuoqiu.gdata.e;
	m_friction=zuoqiu.gdata.friction;
	m_impulls=zuoqiu.gdata.impulls;
	m_timstep=zuoqiu.gdata.timstep;
	m_fps=zuoqiu.gdata.fps;
	m_bcheckstickcollid=zuoqiu.gdata.bcheckstickcollid;
	m_mouserev=zuoqiu.gdata.mouserev;
	zuoqiu.initui();
	inittimer();
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!GetMessage(&msg, NULL, 0, 0))
			{
				return msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(_fps>m_fps*ticks_per_ms)
		{
			if(IsMinimized == FALSE && (ActiveApp && !FullScreen))
			{
				_speed=gettimer();//GetTickCount();
				DoFrame();
				_fps=(gettimer()-_speed);
			}
			else{	WaitMessage();	}
		}
		else
		{
			_fps=(gettimer()-_speed);
		}
	}
}


void DoFrame(){
	if(SwitchMode){
		_m_buf.SetBufferMode(WIDTH, HEIGHT, BPP, FullScreen, &tcf);
		_m_buf.SetWindowSize(WIDTH, HEIGHT);
		_m_buf.SetPalette(NULL);
		_m_buf.RealizePalette();
		SwitchMode = FALSE;
	}

	//SetCursorPos(500,500);
	if(_m_buf.Lock(&_m_bd))
	{
		clearscr();

		zuoqiu.gameloop();
		zuoqiu.gameinputloop();

		drawfps();
		/*if(zuoqiu.gdata.gamesta==GST_XUMU)
		{
			print_num(8,14 ,mmgams,1);
			print_num(8,24, (int)(tmstep*1000), 1);
			if(getkey('9'))mmgams+=mmkeys;
			else if(getkey('0'))
			{
				mmgams-=mmkeys;
				if(mmgams<0)mmgams=0;
			}
			else if(getkey('7'))mmkeys+=1;
			else if(getkey('8'))
			{
				mmkeys-=1;
				if(mmkeys<0)mmkeys=0;
			}
			else if(getkey('5'))tmstep+=0.001f;
			else if(getkey('6'))
			{
				tmstep-=0.001f;
				if(tmstep<0)tmstep=0;
			}
		}*/
		_m_buf.Unlock();
	}		
	fps=gettimetick();
	_m_buf.UpdateFrontBuffer(FullScreen ? NULL : UFB_STRETCH);	//Call UpdateFrontBuffer while UNLOCKED.
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	zuoqiu.MsgProcUI(hwnd,iMsg,wParam,lParam);
	switch(iMsg){
		case WM_ACTIVATEAPP :
			ActiveApp = wParam;
			if(ActiveApp==0)
				ShowCur();
			break;
		case WM_ACTIVATE :
			IsMinimized = HIWORD(wParam);
			break;
		case WM_CREATE :
			return 0;
		case WM_MOUSEWHEEL:
			{
				if(zuoqiu.gdata.gamesta!=GST_GAMING)break;
				if (HIWORD(wParam)==120)
					zuoqiu.balltick.zoomcam(-1);
				else
					zuoqiu.balltick.zoomcam(1);
			}
			break;
		case WM_LBUTTONDOWN:
			MouseX = LOWORD(lParam);
			MouseY = HIWORD(lParam);
			lmclked=true;
			break;
		case WM_LBUTTONUP:
			{
				lmclked=false;
				zuoqiu.actmousebar();
				break;
			}
		case WM_RBUTTONDOWN:rmclked=true;break;
		case WM_RBUTTONUP:rmclked=false;break;
		case WM_MOUSEMOVE :
			{
				if(zuoqiu.gdata.gamesta!=GST_GAMING)break;
				POINT pt={WIDTH*0.5f,HEIGHT*0.5f};
				MouseX=mx= LOWORD(lParam);
				MouseY=my= HIWORD(lParam);
				if(false==bmouse)
				{
					if(rmclked)
					{
						//RDev.SysCamera->TransefCameraByMouse1( (mx-pt.x)*100,(my-pt.y)*100);
						zuoqiu.balltick.RotateCamByMouse((mx-pt.x)*100,(my-pt.y)*100);
					}
					else {zuoqiu.balltick.updata(mx-pt.x,my-pt.y);}
				}
				omx=mx;omy=my;
			}
			break;
		case WM_KEYDOWN :
			_m_wparam=wParam;
			switch(wParam){
				case VK_ESCAPE :
					{

					//	PostMessage(hwnd, WM_CLOSE, NULL, NULL);
					}
					break;
				case VK_F1:
					{
						zuoqiu.m_helpdlg.SetVisible(!zuoqiu.m_helpdlg.GetVisible());
					}
					break;
				case VK_RETURN:
					{
					
					}
					break;
				case VK_F8 :
					FullScreen = !FullScreen;
					SwitchMode = TRUE;
					break;
			}
			break;
		case WM_KEYUP:{	_m_wparam=0;}

		case WM_PAINT :
			BeginPaint(hwnd, &ps);
			_m_buf.UpdateFrontBuffer(FullScreen ? NULL : UFB_STRETCH);
			EndPaint(hwnd, &ps);
			return 0;
		case WM_CLOSE :
			DestroyWindow(hwnd);
			return 0;
		case WM_DESTROY :
			hWnd = NULL;
			_m_buf.Destroy();
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}


void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, UIControl* pControl )
{;
}


















