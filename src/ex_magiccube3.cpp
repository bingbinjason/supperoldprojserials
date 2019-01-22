
	  
#include "core.h"
int news=0,dels=0,fals=0;


enum GAMESTA{GST_XUMU,GST_MNU,GST_START,GST_END,GST_GAMEING,GST_CONTINUE,GST_PAUSE,GST_WIN,GST_LOSE,};
enum EFTTYP{EFT_WIN,EFT_LOSE,EFT_XUMU,EFT_XUMU1,EFT_XUMU2,EFT_ROT,EFT_ROT1,EFT_PTC,EFT_ROTV,};

#define UNITSIZE 50
#define MAGCUBESIZE 3
#define WW 11
#define HH 1

Camera cm;
RenderDevice *RD;

enum _DERECTION{_R=0,_D,_B,_L,_F,_U,_DMAX};
enum _OBIT{_X=0,_Y,_Z,_OMAX};
Vector3 VecVec[]={Vector3(1,0,0),Vector3(0,1,0),Vector3(0,0,1),Vector3(-1,0,0),Vector3(0,0,-1),Vector3(0,-1,0)};
typedef int RotStep[3]; //0 :_OBIT,	1: floor, 2: +/-
Matrix4 mat[3][2]={
	{Rotate(0,0,0, 90,'x'),	Rotate(0,0,0,-90,'x'),},
	{Rotate(0,0,0, 90,'y'),	Rotate(0,0,0,-90,'y'),},
	{Rotate(0,0,0, 90,'z'),	Rotate(0,0,0,-90,'z'),},
};
/*mat[0][0]=Rotate(0,0,0, 90,'x');
mat[0][1]=Rotate(0,0,0,-90,'x');
mat[1][0]=Rotate(0,0,0, 90,'y');
mat[1][1]=Rotate(0,0,0,-90,'y');
mat[2][0]=Rotate(0,0,0, 90,'z');
mat[2][1]=Rotate(0,0,0,-90,'z');*/


struct _gamedata	//独立出来的游戏中间数据(对于多人游戏才有的特别设计)
{
	//地图数据
	int magcubsize;
	int blocksize;
	Point3 startpos;
	int defcul;
	GAMESTA gamesta;
	_gamedata(){init();};
	void init()
	{
		magcubsize=MAGCUBESIZE;
		blocksize=UNITSIZE;
		startpos=Point3(0,0,0);
		defcul=0;
		gamesta=GST_XUMU;
	}
};

struct _player	//游戏玩家中间数据
{
	char name[16];
	char id;
	char score;
};

class CubeUnit
{
public:
	Vector3 pos,tpos,upos;
	Vector3 xyz[3],txyz[3];
	Point3 rotxyz;
	float rotdeg;
	_gamedata *gdt;
	char m_color[_DMAX];//相对坐标系颜色
	char m_wcolor[_DMAX];//世界坐标系颜色
	bool bshow;
public:
	CubeUnit()
	{
		Init();
	};
	void Init()
	{
		gdt=NULL;
		bshow=true;
		upos=pos=tpos=Point3(0,0,0);
		xyz[0]=txyz[0]=Point3(1,0,0);
		xyz[1]=txyz[1]=Point3(0,1,0);
		xyz[2]=txyz[2]=Point3(0,0,1);
		rotxyz=Point3(0,0,0);
		rotdeg=0;
		memset(m_color,0,sizeof(char)*6);
	};
	void SetGamedata(_gamedata *dt){gdt=dt;};
	void SetPosByUnit(int x,int y,int z,bool breal=true)
	{
		upos=Point3(x,y,z);
		if(breal)
		{
			float pp=gdt->magcubsize-1;
			pp=pp/2.0f * UNITSIZE*2;
			tpos=pos=upos*UNITSIZE*2- Point3(pp,pp,pp);
		}
	}
	void SetPos(float x,float y,float z)
	{
		tpos=pos=Point3(x,y,z);
	};
	void SetColor(_DERECTION dir,char clr)
	{
		m_color[dir]=clr;
		m_wcolor[dir]=clr;
	}
	void RotColor(int txyz,int dir,bool bclr=true)
	{
		char tmp;
		switch(txyz)
		{
		case _X:
			{
				if(dir==0)//前
				{
					tmp=m_wcolor[_F];
					m_wcolor[_F]=m_wcolor[_U];
					m_wcolor[_U]=m_wcolor[_B];
					m_wcolor[_B]=m_wcolor[_D];
					m_wcolor[_D]=tmp;
				}
				else if(dir==1)//后
				{
					tmp=m_wcolor[_F];
					m_wcolor[_F]=m_wcolor[_D];
					m_wcolor[_D]=m_wcolor[_B];
					m_wcolor[_B]=m_wcolor[_U];
					m_wcolor[_U]=tmp;
				}
			}
			break;
		case _Y:
			{
				if(dir==0)//顺
				{
					tmp=m_wcolor[_F];
					m_wcolor[_F]=m_wcolor[_R];
					m_wcolor[_R]=m_wcolor[_B];
					m_wcolor[_B]=m_wcolor[_L];
					m_wcolor[_L]=tmp;
				}
				else if(dir==1)//逆
				{
					tmp=m_wcolor[_F];
					m_wcolor[_F]=m_wcolor[_L];
					m_wcolor[_L]=m_wcolor[_B];
					m_wcolor[_B]=m_wcolor[_R];
					m_wcolor[_R]=tmp;
				}
			}
			break;
		case _Z:
			{
				if(dir==0)//顺
				{				
					tmp=m_wcolor[_U];
					m_wcolor[_U]=m_wcolor[_L];
					m_wcolor[_L]=m_wcolor[_D];
					m_wcolor[_D]=m_wcolor[_R];
					m_wcolor[_R]=tmp;
					
				}
				else if(dir==1)//逆时针
				{
					tmp=m_wcolor[_U];
					m_wcolor[_U]=m_wcolor[_R];
					m_wcolor[_R]=m_wcolor[_D];
					m_wcolor[_D]=m_wcolor[_L];
					m_wcolor[_L]=tmp;
				}
				
			}
			break;
		}
		for(int i=0;i<_DMAX;i++)
			m_color[i]=m_wcolor[i];
	};
	void SetShow(bool bsh=true)
	{
		bshow=bsh;
	};
	void AlignCoord()
	{
		;//规整坐标系
	};
	void Rot(int tpxyz,int dir)//只旋转坐标系
	{
		Point3 sxyz=VecVec[tpxyz];
		if(dir==0)sxyz=sxyz*90;
		else sxyz=sxyz*-90;

		Quat qt=Quat(Point3(1,0,0),sxyz[_X]*Pi)*Quat(Point3(0,1,0),sxyz[_Y]*Pi)*Quat(Point3(0,0,1),sxyz[_Z]*Pi);
		qt.Unit();
		xyz[0]=xyz[0]*qt;xyz[0].Unit();
		xyz[1]=xyz[1]*qt;xyz[1].Unit();
		xyz[2]=xyz[2]*qt;xyz[2].Unit();
		txyz[0]=xyz[0];
		txyz[1]=xyz[1];
		txyz[2]=xyz[2];
/*		float d=pos.Mod();
		pos.Unit();
		pos=pos*qt;
		pos.Unit();
		pos=pos*d;
*/
	};
	void SetRot(int tpxyz,float deg)
	{
		rotxyz=VecVec[tpxyz];
		int dg=(int)(deg+0.5f);
		dg=dg%360;
		rotdeg=dg;
		
/*		Quat qt0=Quat(rotxyz,rotdeg*Pi);
		txyz[_X]=xyz[_X]*qt0;txyz[_X].Unit();
		txyz[_Y]=xyz[_Y]*qt0;txyz[_Y].Unit();
		txyz[_Z]=xyz[_Z]*qt0;txyz[_Z].Unit();
		tpos=pos;
		float d=tpos.Mod();
		tpos.Unit();
		tpos=tpos*qt0;
		tpos.Unit();
		tpos=tpos*d;
*/
	};
	void DrawQuad(Point3 *p,char c=2)
	{
		if(0==c)return;

		Quat qt0=Quat(rotxyz,rotdeg*Pi);
		tpos=pos;
		float d=tpos.Mod();
		tpos.Unit();
		tpos=tpos*qt0;
		tpos.Unit();
		tpos=tpos*d;
		for(int i=0;i<5;i++)
		{
			d=p[i].Mod();
			p[i].Unit();
			p[i]=p[i]*qt0;
			p[i].Unit();
			p[i]=p[i]*d;
		}

		Vector3 vc0,vc=p[4],vdr=RD->SysCamera->ViewDir;
		vc.Unit();
		if( (vc*vdr)>=0)
		{

			Line3(p[0]+tpos,p[1]+tpos,c);	
			Line3(p[1]+tpos,p[2]+tpos,c);	
			Line3(p[2]+tpos,p[3]+tpos,c);	
			Line3(p[3]+tpos,p[0]+tpos,c);
			if(check1col(p))
				DrawSphere(p[4]+tpos,2,c);
		}
/*		else 
		{
			Line3(p[0]+tpos,p[1]+tpos,34);	
			Line3(p[1]+tpos,p[2]+tpos,34);	
			Line3(p[2]+tpos,p[3]+tpos,34);	
			Line3(p[3]+tpos,p[0]+tpos,34);
		}
*/
	};
	void GetVert10(_DERECTION dir,Point3 *p=NULL)
	{
		if(p==NULL)return;
		Quat qt;
//		xyz[0].Unit();xyz[1].Unit();xyz[2].Unit();

		p[0]=txyz[0]*-UNITSIZE + txyz[1]*-UNITSIZE + txyz[2]*-UNITSIZE + Point3( 5, 5,0);
		p[1]=txyz[0]* UNITSIZE + txyz[1]*-UNITSIZE + txyz[2]*-UNITSIZE + Point3(-5, 5,0);
		p[2]=txyz[0]* UNITSIZE + txyz[1]* UNITSIZE + txyz[2]*-UNITSIZE + Point3(-5,-5,0);
		p[3]=txyz[0]*-UNITSIZE + txyz[1]* UNITSIZE + txyz[2]*-UNITSIZE + Point3( 5,-5,0);
		p[4]=txyz[2]*-UNITSIZE;
		p[5]=txyz[1]*-(UNITSIZE-5) + txyz[2]*-UNITSIZE;
		p[6]=txyz[0]* (UNITSIZE-5) + txyz[2]*-UNITSIZE;
		p[7]=txyz[1]* (UNITSIZE-5) + txyz[2]*-UNITSIZE;
		p[8]=txyz[0]*-(UNITSIZE-5) + txyz[2]*-UNITSIZE;
		switch(dir)
		{
		case _F:	return;		break;
		case _L:	{	qt=Quat(txyz[1],90*Pi);qt.Unit();}	break;
		case _B:	{	qt=Quat(txyz[1],180*Pi);qt.Unit();}	break;
		case _R:	{	qt=Quat(txyz[1],270*Pi);qt.Unit();}	break;
		case _D:	{	qt=Quat(txyz[1],270*Pi)*Quat(txyz[2],90*Pi);qt.Unit();}	break;
		case _U:	{	qt=Quat(txyz[1],270*Pi)*Quat(txyz[2],-90*Pi);qt.Unit();}	break;
		}
		int ll;
		for(int i=0;i<9;i++)
		{
			ll=p[i].Mod();
			p[i]=p[i]*qt;
			p[i].Unit();
			p[i]=p[i]*ll;
		}
	}
	bool check1col(Point3 *p)
	{
		bool colid=false;
		RayT ray=RD->GetMouseVec(mx,my);
		Vector3 vec[3];
		Vector3 vc=p[4],vdr=RD->SysCamera->ViewDir;
		vc.Unit();
		if( (vc*vdr)>0 )
		{
			vec[0]=p[0]+pos;	vec[1]=p[1]+pos;	vec[2]=p[2]+pos;
			colid=RayIntersectsCullTriangle(ray.start,ray.end,vec);
			if(colid==true)return true;
			vec[0]=p[0]+pos;	vec[1]=p[2]+pos;	vec[2]=p[3]+pos;
			colid=RayIntersectsCullTriangle(ray.start,ray.end,vec);
			if(colid==true)return true;		
		}
		return false;
	};
	int checkcol()
	{
		Point3 p[10];
		for(int i=0;i<_DMAX;i++)
		{
			if(m_color[i]==0)continue;
			GetVert10((_DERECTION)i,p);
			if(check1col(p))
			{
			//	DrawSphere(p[4]+pos,2,2);
				return i;
			}
		}
		return _DMAX;
	};
	void Draw()
	{
		if(false==bshow)return;
	//	DrawCoord(pos,xyz[0],xyz[1],xyz[2]);
		Point3 p[10];
		for(int i=0;i<_DMAX;i++)
		{
			GetVert10((_DERECTION)i,p);
			DrawQuad(p,m_color[i]);
		}
	};

private:
	
};
struct Eftstr 
{
	EFTTYP Eftp;
	unsigned int dtime,lagtime;
	int prt[5];
	bool bcontinue;

	Point3 ps;
	Point3 ps1,ps2,ps3;
	ptc m_ptc[20];
	ORECT ort;
	Quat qt0,qt1;
	
	Eftstr(){init();}
	void init()
	{
		bcontinue=false;
		ps=Point3(0,0,0);
		memset(prt,0,sizeof(int)*5);
	};
};

static int _floor=-1,_obite=-1,_dir=-1;

class MagicCube3D
{
public:
	
	MagicCube3D(){};
	~MagicCube3D(){};

	void Init();
	bool check1bingo(int dir)
	{
		int floor,xyz;
		if(dir==_L){xyz=_X;floor=0;}
		else if(dir==_R){xyz=_X;floor=gdata.magcubsize-1;}
		else if(dir==_U){xyz=_Y;floor=0;}
		else if(dir==_D){xyz=_Y;floor=gdata.magcubsize-1;}
		else if(dir==_F){xyz=_Z;floor=0;}
		else if(dir==_B){xyz=_Z;floor=gdata.magcubsize-1;}
		
		int ix,iy,iz,sxyz[3],dxyz[3];
		sxyz[0]=sxyz[1]=sxyz[2]=0;
		dxyz[0]=dxyz[1]=dxyz[2]=gdata.magcubsize;
		sxyz[xyz]=floor;dxyz[xyz]=floor+1;
		char clr=0,clr1;
		for(ix=sxyz[_X];ix<dxyz[_X];ix++)
		{
			for(iy=sxyz[_Y];iy<dxyz[_Y];iy++)
			{
				for(iz=sxyz[_Z];iz<dxyz[_Z];iz++)
				{
					if(clr!=0 && clr!=m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].m_wcolor[dir])
						return false;
					clr=m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].m_wcolor[dir];
				}
			}
		}
		return true;
	}
	bool checkbingo()
	{
		if(!check1bingo(_F))return false;
		if(!check1bingo(_D))return false;
		if(!check1bingo(_R))return false;
		return true;
	}
	void SetRot(int xyz,int floor,float deg)
	{
		int ix,iy,iz,sxyz[3],dxyz[3];
		sxyz[0]=sxyz[1]=sxyz[2]=0;
		dxyz[0]=dxyz[1]=dxyz[2]=gdata.magcubsize;
		sxyz[xyz]=floor;dxyz[xyz]=floor+1;
		
		for(ix=sxyz[_X];ix<dxyz[_X];ix++)
		{
			for(iy=sxyz[_Y];iy<dxyz[_Y];iy++)
			{
				for(iz=sxyz[_Z];iz<dxyz[_Z];iz++)
				{
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].SetRot(xyz,deg);
				}
			}
		}
	};
	Point3 Rot90(Point3 pt,int num,int xyz,int dir)
	{
		float half=(num-1)/2;
		int t=num-1;
		Point3 retp=pt;
		if(xyz==_Z)
		{
			if(dir==0)//顺时针
			{
				retp.x=t-pt.y;
				retp.y=pt.x;
			}
			else if(dir==1)
			{
				retp.x=pt.y;
				retp.y=t-pt.x;
			}
		}
		else if(xyz==_X)
		{
			if(dir==1)//顺时针
			{
				retp.z=t-pt.y;
				retp.y=pt.z;
			}
			else if(dir==0)
			{
				retp.z=pt.y;
				retp.y=t-pt.z;
			}
		}
		else if(xyz==_Y)
		{
			if(dir==1)//顺时针
			{
				retp.x=t-pt.z;
				retp.z=pt.x;
			}
			else if(dir==0)
			{
				retp.x=pt.z;
				retp.z=t-pt.x;
			}
		}
		return retp;
	}
	void Rot(int xyz,int floor,int dir)
	{				
		int tx,ty,tz;
		int ix,iy,iz,sxyz[3],dxyz[3];
		sxyz[0]=sxyz[1]=sxyz[2]=0;
		dxyz[0]=dxyz[1]=dxyz[2]=gdata.magcubsize;
		sxyz[xyz]=floor;dxyz[xyz]=floor+1;

		int t=gdata.magcubsize*gdata.magcubsize*gdata.magcubsize;
		CubeUnit *tmpUnit = new CubeUnit[t];

		for(ix=sxyz[_X];ix<dxyz[_X];ix++)
		{
			for(iy=sxyz[_Y];iy<dxyz[_Y];iy++)
			{
				for(iz=sxyz[_Z];iz<dxyz[_Z];iz++)
				{
					Point3 pt1=Rot90(Point3(ix,iy,iz),gdata.magcubsize,xyz,dir);
//					Point3 pt=( Point3(ix,iy,iz)-Point3(1,1,1) ) * mat[xyz][dir];
//					V_ROUND(pt);
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].SetPosByUnit(pt1.x,pt1.y,pt1.z,true);
					//m_unit[iz*magcubsize*magcubsize +iy*magcubsize+ix].Rot(xyz,dir);
//					pt=pt+Point3(1,1,1);
					tx=pt1.x;ty=pt1.y;tz=pt1.z;
//					DrawSphere(Point3(tx,ty,tz)*100,2,2);
					tmpUnit[tz*gdata.magcubsize*gdata.magcubsize +ty*gdata.magcubsize+tx]=
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix];
				}
			}
		}
		for(ix=sxyz[_X];ix<dxyz[_X];ix++)
		{
			for(iy=sxyz[_Y];iy<dxyz[_Y];iy++)
			{
				for(iz=sxyz[_Z];iz<dxyz[_Z];iz++)
				{
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix]=
						tmpUnit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix];
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].RotColor(xyz,dir,true);
					//m_unit[iz*magcubsize*magcubsize +iy*magcubsize+ix].SetShow();
				}
			}
		}
		delete[] tmpUnit;

		if(checkbingo())
		{
			startwinani();
		}
	};
	void CheckShow()
	{
		int i=0;
		for(i=0;i<_DMAX;i++)
		{
			if(VecVec[i]*RD->SysCamera->ViewDir <0 )
				SetShow((_DERECTION)i,false);
		}	
		for(i=0;i<_DMAX;i++)
		{
			if(VecVec[i]*RD->SysCamera->ViewDir >=0 )
				SetShow((_DERECTION)i,true);
		}	
	};
	void SetColor(_DERECTION dir,char clr)
	{
		int ix=0,iy=0,iz=0;
		switch(dir)
		{
		case _U:
			{	for(ix=0;ix<gdata.magcubsize;ix++)
				for(iz=0;iz<gdata.magcubsize;iz++)
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +0*gdata.magcubsize+ix].SetColor(dir,clr);}break;
		case _D:
			{	for(ix=0;ix<gdata.magcubsize;ix++)
				for(iz=0;iz<gdata.magcubsize;iz++)
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +(gdata.magcubsize-1)*gdata.magcubsize+ix].SetColor(dir,clr);}break;
		case _L:
			{	for(iy=0;iy<gdata.magcubsize;iy++)
				for(iz=0;iz<gdata.magcubsize;iz++)
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+0].SetColor(dir,clr);}break;
		case _R:
			{	for(iy=0;iy<gdata.magcubsize;iy++)
				for(iz=0;iz<gdata.magcubsize;iz++)
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+(gdata.magcubsize-1)].SetColor(dir,clr);}break;
		case _F:
			{	for(ix=0;ix<gdata.magcubsize;ix++)
				for(iy=0;iy<gdata.magcubsize;iy++)
					m_unit[0*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].SetColor(dir,clr);}break;
		case _B:
			{	for(ix=0;ix<gdata.magcubsize;ix++)
				for(iy=0;iy<gdata.magcubsize;iy++)
					m_unit[(gdata.magcubsize-1)*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].SetColor(dir,clr);}break;
		}
	};
	void SetShow(_DERECTION dir,bool bsh=true)
	{
		int ix=0,iy=0,iz=0;
		switch(dir)
		{
		case _U:
			{	for(ix=0;ix<gdata.magcubsize;ix++)
					for(iz=0;iz<gdata.magcubsize;iz++)
						m_unit[iz*gdata.magcubsize*gdata.magcubsize +0*gdata.magcubsize+ix].SetShow(bsh);}break;
		case _D:
			{	for(ix=0;ix<gdata.magcubsize;ix++)
					for(iz=0;iz<gdata.magcubsize;iz++)
						m_unit[iz*gdata.magcubsize*gdata.magcubsize +(gdata.magcubsize-1)*gdata.magcubsize+ix].SetShow(bsh);}	break;
		case _L:
			{	for(iy=0;iy<gdata.magcubsize;iy++)
					for(iz=0;iz<gdata.magcubsize;iz++)
						m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+0].SetShow(bsh);}	break;
		case _R:
			{	for(iy=0;iy<gdata.magcubsize;iy++)
					for(iz=0;iz<gdata.magcubsize;iz++)
						m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+(gdata.magcubsize-1)].SetShow(bsh);}	break;
		case _F:
			{	for(ix=0;ix<gdata.magcubsize;ix++)
					for(iy=0;iy<gdata.magcubsize;iy++)
						m_unit[0*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].SetShow(bsh);}	break;
		case _B:
			{	for(ix=0;ix<gdata.magcubsize;ix++)
					for(iy=0;iy<gdata.magcubsize;iy++)
						m_unit[(gdata.magcubsize-1)*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].SetShow(bsh);}	break;
		}
	};
	bool Getselcubeinfo()//通过鼠标控制获取操作指令
	{
		if(broting)return false;
		int unitdir=_DMAX;CubeUnit *cu;
		int ix,iy,iz;ORECT _ort;RayT _ray;
		for(ix=0;ix<gdata.magcubsize;ix++)
			for(iy=0;iy<gdata.magcubsize;iy++)
				for(iz=0;iz<gdata.magcubsize;iz++)
				{
//					if(m_unit[iz*magcubsize*magcubsize +iy*magcubsize+ix].bshow==false)continue;
					cu=&m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix];
					_ort=ORECT(cu->pos,Point3(UNITSIZE,UNITSIZE,UNITSIZE));
					_ort.SetAxis(cu->xyz[0],cu->xyz[1],cu->xyz[2]);
					_ray=RD->GetMouseVec(mx,my);
					_ray.end=_ray.end*-1;
					
					if(!RayOBBOverlap(_ray,_ort))continue;

					if( (unitdir=m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].checkcol())!=_DMAX)
					{
						m_currentpos=Point3(ix,iy,iz);
						m_currentdir=unitdir;
						return true;
					}
				}
		return false;
	};
	bool GetOpr()
	{
		if(broting)return false;
		int ot,dir;
		Vector3 vc,vc1[4];
		vc=Vector3(mx-MouseX,my-MouseY,0);
		float vcl=vc.Mod();
		if(vcl<3)
		{
			tiping=1;
			tiptime=GetTickCount();
			return false;
		}
		vc.Unit();
		vc1[3]=Rasterize(Vector3(0,0,0));vc1[3].z=0;
		vc1[0]=Rasterize(Vector3(1,0,0)*10);vc1[0].z=0;
		vc1[1]=Rasterize(Vector3(0,1,0)*10);vc1[1].z=0;
		vc1[2]=Rasterize(Vector3(0,0,1)*10);vc1[2].z=0;
		vc1[0]=vc1[0]-vc1[3];
		vc1[1]=vc1[1]-vc1[3];
		vc1[2]=vc1[2]-vc1[3];
		
		int obt=_OMAX,obt1=_OMAX,ot1=_OMAX;
		float ang[3],png;int tpxyz[3],dr[3],tmp;
		tpxyz[_X]=_X;tpxyz[_Y]=_Y;tpxyz[_Z]=_Z;
		dr[_X]=dr[_Y]=dr[_Z]=1;
		if(m_currentdir==_L||m_currentdir==_R)ot1=_X;
		else if(m_currentdir==_U||m_currentdir==_D)ot1=_Y;
		else if(m_currentdir==_F||m_currentdir==_B)ot1=_Z;
		ang[0]=GetAngel(vc,vc1[0]);
		ang[1]=GetAngel(vc,vc1[1]);
		ang[2]=GetAngel(vc,vc1[2]);
		if(ang[0]>90 && ang[0]!=360)
		{	ang[0]=180-ang[0];dr[0]=-1;	}
		if(ang[1]>90 && ang[1]!=360)
		{	ang[1]=180-ang[1];dr[1]=-1;	}
		if(ang[2]>90 && ang[2]!=360)
		{	ang[2]=180-ang[2];dr[2]=-1;	}

		if(ang[0]>ang[1])
		{
			tmp=ang[0];
			ang[0]=ang[1];
			ang[1]=tmp;
			tmp=tpxyz[0];
			tpxyz[0]=tpxyz[1];
			tpxyz[1]=tmp;
		}
		if(ang[0]>ang[2])
		{
			tmp=ang[0];
			ang[0]=ang[2];
			ang[2]=tmp;
			tmp=tpxyz[0];
			tpxyz[0]=tpxyz[2];
			tpxyz[2]=tmp;
		}
		if(ang[1]>ang[2])
		{
			tmp=ang[1];
			ang[1]=ang[2];
			ang[2]=tmp;
			tmp=tpxyz[1];
			tpxyz[1]=tpxyz[2];
			tpxyz[2]=tmp;
		}
		if(ang[2]==360)//无角度
		{
			ang[2]=ang[1];
			tpxyz[2]=tpxyz[1];
		}
//		if(ang[0]< ang[2]) )
//		{
		if(tpxyz[0]!=ot1){	ot=tpxyz[0];dir=dr[tpxyz[0]];	}
		else {ot=tpxyz[1];dir=dr[tpxyz[1]];}
//		}
//		else
//		{
//			if(tpxyz[2]!=ot1){ot=tpxyz[2];dir=-1;}
//			else {ot=tpxyz[0];dir=1;};
//			
//		}

/*		float png=0,ang=360,ang1=0;
		for(int i=0;i<_OMAX;i++)
		{
			ang1=GetAngel(vc,vc1[i]);
			if(ang1<ang)//最好优化成点积形式来判断（即投影）
			{
				obt=i;
				ang=ang1;
			}
			if(ang1>png)
			{
				obt1=i;
				png=ang1;
			}
		}
		if(png>90)png=180-png;
		if(ang<png){ot=obt;dir=1;}
		else { ot=obt1;dir=-1;} 
*/
		if(m_currentdir!=_DMAX)//产生鼠标点击的方块
		{
			Point3 t1=VecVec[m_currentdir];
			Point3 t2=VecVec[ot]*dir;
			Point3 t3=t1|t2;t3.Unit();
			int ot2,rotdir,floor;
/*			if(m_currentdir==_L||m_currentdir==_R)ot1=_X;
			else if(m_currentdir==_U||m_currentdir==_D)ot1=_Y;
			else if(m_currentdir==_F||m_currentdir==_B)ot1=_Z;
*/
			if(ot==ot1)return false;
			if( (ot==_X && ot1==_Y) || (ot1==_X && ot==_Y) )ot2=_Z;
			if( (ot==_X && ot1==_Z) || (ot1==_X && ot==_Z) )ot2=_Y;
			if( (ot==_Z && ot1==_Y) || (ot1==_Z && ot==_Y) )ot2=_X;
			rotdir= (t3*VecVec[ot2]<0)?-1:1;
			floor=m_currentpos[ot2];

			_floor=floor;_obite=ot2;_dir=rotdir;
			RotStep stp;stp[0]=_obite;stp[1]=_floor;stp[2]=_dir;
			m_StepList.Append(stp);
			if(m_StepList.Entries()>10)
				m_StepList.Remove(0);
			m_step+=1;
			startrot(_obite,_floor,_dir);
		}
	}

	void Loop();
	void DrawMenu()
	{
		static int chs=0;
		static int dif=1;
		static int dis=0;
		print_string(140,100,2,"Game Start");
		if(dif==0)	print_string(140,140,2,"CubeSize 2*2");
		else if(dif==1)print_string(140,140,2,"CubeSize 3*3");
		else if(dif==2)print_string(140,140,2,"CubeSize 4*4");
		if(dis==0)print_string(140,180,2,"Display Perp");
		else print_string(140,180,2,"Display Ortho");
		print_string(132,100+chs*40,9,"*");

		if(getkey(VK_UP,true))chs-=1;
		else if(getkey(VK_DOWN,true))chs+=1;
		else if(getkey(VK_RETURN,true))
		{
			if(chs==0)
			{
				gdata.gamesta=GST_GAMEING;
				gamestart();
			}
			else if(chs==1)
			{
				dif+=1;if(dif>2)dif=0;
				cubesize=dif+2;
				gdata.magcubsize=cubesize;
			}
			else if(chs==2)
			{
				dis=0;//+=1;if(dis>1)dis=0;
				prjtyp=dis;
				if(dis==0)RD->SysCamera->vWorldScale=1;
				else RD->SysCamera->vWorldScale=0.2f;
			}
		}
		if(chs<0)chs=2;
		else if(chs>2)chs=0;

	};
	void DrawBk()
	{
		print_string(6,2,32,"BinfenSoft Studio(C)");
		Line_(6,12,394,294,32,true);
	}
	void Drawscore()
	{
		Line_(8,250,392,292,32,true);
		print_string(20,260,2,"Step:");
		print_string(20,276,2,"Time:");
		
//		print_string(64,260,2,"000");

		print_string(64,276,2,"00:00:00");
		print_num(64,260,m_step,2,1);
		print_num(64,276,m_time,2);

		print_string(280,262,2,"Press <F1>");
		print_string(286,274,2,"for help");
	};
	void Destroy();
	void Effectloop()
	{
		Eftstr *eftstr;
		bool bres=true;
		for(eftstr=Eftlst.GetFirst();eftstr!=NULL;eftstr=Eftlst.GetNext())
		{
			switch(eftstr->Eftp)
			{
				case EFT_XUMU:{bres=loopxumuani(eftstr);break;}
				case EFT_XUMU1:{bres=loopxumuani1(eftstr);break;}
				case EFT_XUMU2:{bres=loopxumuani2(eftstr);break;}
				case EFT_ROT:{bres=looprotani(eftstr);break;}
				case EFT_ROT1:{bres=looprot1ani(eftstr);break;}
				case EFT_PTC:{bres=loopptcani(eftstr);break;}
				case EFT_WIN:{bres=loopwinani(eftstr);break;}
				case EFT_ROTV:{bres=looprotv(eftstr);break;}
			}
			if(bres==false)
			{
				Eftlst.Delete();//非物理删除;
				delete eftstr;
				dels+=1;
			}
		}
	};
	void freealleft()
	{
//		for(i=0;i<Eftlst.GetSize();i++)
		Eftlst.Free();
	}


	void startrot1(int rotcod,int floor,int rotdeg)
	{
		Eftstr *estr=new Eftstr;
		if(estr==NULL){fals+=1;return;};
		news+=1;
		estr->Eftp=EFT_ROT1;
		estr->dtime=gettimetick();
		estr->lagtime=0;
		float pt[]={UNITSIZE*gdata.magcubsize,UNITSIZE*gdata.magcubsize,UNITSIZE*gdata.magcubsize};
		pt[rotcod]=UNITSIZE;
		float pt1[]={0,0,0};
		float ff=gdata.magcubsize-1;
		ff=(float)(floor)-ff/2.0f;
		pt1[rotcod]=ff*UNITSIZE*2;
		estr->ort=ORECT(Point3(pt1),Point3(pt));
		Quat qt=Quat(VecVec[rotcod],rotdeg*Pi);
		estr->ort.SetRot(qt);

		estr->prt[0]=rotcod;
		estr->prt[1]=floor;
		estr->prt[2]=rotdeg;
		Eftlst.Push(estr);
	}
	void startrot(int rotcod,int floor,int rotdir,int bcn=0,bool bc=false)
	{
		if(broteftdone==false)return;
		if(acting==true)return;
		Eftstr *estr=new Eftstr;
		if(estr==NULL){fals+=1;return;};
		news+=1;
		estr->Eftp=EFT_ROT;
		estr->dtime=gettimetick();
		estr->lagtime=0;
		estr->prt[0]=rotcod;
		estr->prt[1]=floor;
		estr->prt[2]=rotdir;
		estr->prt[3]=bcn;
		estr->bcontinue=bc;
		Eftlst.Push(estr);
		broting=true;
		broteftdone=false;
	};
	void startptc(Point3 pt,int clr=1,int tp=0)
	{
		Eftstr *estr=new Eftstr;
		if(estr==NULL){fals+=1;return;};
		news+=1;
		estr->Eftp=EFT_PTC;
		estr->dtime=gettimetick();
		estr->lagtime=0;
		estr->prt[0]=clr * 7 +1;
		Point3 vv=Point3(0,0,0);

		for(int i=0;i<20;i++)
		{		
			if(tp==0)
			{
				vv=Point3(rand()%10-rand()%10,(rand()%40+20)*-1,rand()%10-rand()%10);
			}
			else if(tp==1)
			{
				vv=Point3(rand()%10-rand()%10,(rand()%20+10)*-1,rand()%10-rand()%10);
			}
			estr->m_ptc[i].s0=pt+Point3(0,-2,0);
			estr->m_ptc[i].makegrav();
			estr->m_ptc[i].v0=vv;
			estr->m_ptc[i].e=-0.5f;
			estr->m_ptc[i].grd=gdata.magcubsize*UNITSIZE;
			estr->m_ptc[i].life=rand()%2000+1000;
			estr->m_ptc[i].dwtime0=GetTickCount();
			estr->m_ptc[i].stoped=false;
		}
		Eftlst.Push(estr);
	};
	void startwinani()
	{
		if(acting)return;
		if(broting)return;
		Eftstr *estr=new Eftstr;
		if(estr==NULL){fals+=1;return;};
		news+=1;
		estr->Eftp=EFT_WIN;
		estr->dtime=gettimetick();
		estr->lagtime=0;
		Eftlst.Push(estr);
		acting=true;
		RD->SysCamera->LookAt(Point3(0,0,-1500),Vector3(0,0,1),Vector3(0,1,0));
		RD->SysCamera->TransefCameraByMouse1(4500,0);
		RD->SysCamera->TransefCameraByMouse1(0,1500);
	};	
	void startrotv(Quat dqt,Quat sqt,int time=0)
	{
		Eftstr *estr=new Eftstr;
		if(estr==NULL){fals+=1;return;};
		news+=1;
		estr->Eftp=EFT_ROTV;
		estr->dtime=gettimetick();
		estr->lagtime=0;
		estr->prt[0]=time;
		estr->ps1=RD->SysCamera->_u;
		estr->ps2=RD->SysCamera->_v;
		estr->ps3=RD->SysCamera->_n;
		estr->ps=RD->SysCamera->p;
		estr->qt1=dqt;
		estr->qt0=sqt;
		Eftlst.Push(estr);
	};
	bool looprotv(Eftstr *eft)
	{
		unsigned int dtime=gettimetick()-eft->dtime;
		if(eft->lagtime)
		{ if(((dtime/1000) <eft->lagtime ))return true;
		else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
		}
		if(dtime>eft->prt[0])return false;
		Quarternion qq,aq,bq;
		aq=Quarternion(eft->qt0.v.x,eft->qt0.v.y,eft->qt0.v.z,eft->qt0.n);
		bq=Quarternion(eft->qt1.v.x,eft->qt1.v.y,eft->qt1.v.z,eft->qt1.n);
		float f=1.0f/(float)eft->prt[0];
		QuaternionSlerp(&qq,&aq,&bq,f*(float)dtime);
		Quat qt=Quat(qq.w,qq.x,qq.y,qq.z);
		qt.Unit();
//		DrawVec3(Point3(0,0,0),Point3(1,0,0)*qt,2);
		RD->SysCamera->SetPRY(qt,eft->ps1,eft->ps2,eft->ps3,eft->ps);
		return true;
	};
	bool loopwinani(Eftstr *eft)
	{
		unsigned int dtime=gettimetick()-eft->dtime;
		if(eft->lagtime)
		{ if(((dtime/1000) <eft->lagtime ))return true;
		else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
		}
		float f=360.0f/2000.0f;
		float i=f*(float)dtime;
		float r=gdata.magcubsize*UNITSIZE*1.3f;
		
		if(dtime>7000)
		{
			freealleft();
			acting=false;
			return false;
		}
		else if(dtime<2000)
		{
			eft->ps1=Point3(cos(i*Pi)*r,gdata.magcubsize*UNITSIZE,sin(i*Pi)*r);
			startptc(eft->ps1,0,0);
		}
		else if(dtime>2000 && dtime<4000)
		{
			float t=r*1.4f/1000.0f;
			f=1000.0f/2000.0f;
			i=f*(float)(dtime-2000);
			eft->ps1=Point3(cos(i*Pi)*r,t*(float)(dtime-2000)*-1.0f + gdata.magcubsize*UNITSIZE,sin(i*Pi)*r);
			startptc(eft->ps1,rand()%9,1);
			eft->ps1=Point3(cos((180+i)*Pi)*r,t*(float)(dtime-2000)*-1.0f + gdata.magcubsize*UNITSIZE,sin((180+i)*Pi)*r);
			startptc(eft->ps1,rand()%9,1);
		}
		return true;
	}
	bool loopptcani(Eftstr *eft)
	{
		unsigned int dtime=gettimetick()-eft->dtime;
		if(eft->lagtime)
		{ if(((dtime/1000) <eft->lagtime ))return true;
		else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
		}
//		if(gdata.gamesta!=GST_GAMEING)return false;	
		int ff;
		for(int i=0;i<20;i++)
		{
			if( eft->m_ptc[i].stoped==false && eft->m_ptc[i].tuchgrds<2 )
			{
				eft->m_ptc[i].dwtime1=GetTickCount()-eft->m_ptc[i].dwtime0;
				if(eft->m_ptc[i].dwtime1 > eft->m_ptc[i].life)
					eft->m_ptc[i].stoped=true;

				eft->m_ptc[i].run();
				ff=6.0f/(float)eft->m_ptc[i].life;
				pset3(eft->m_ptc[i].s,eft->prt[0]+ ff*(float)eft->m_ptc[i].dwtime1);
			}
		}
		if(dtime>6000)return false;
		return true;
	}
	bool looprot1ani(Eftstr *eft)
	{
		unsigned int dtime=gettimetick()-eft->dtime;
		if(eft->lagtime)
		{ if(((dtime/1000) <eft->lagtime ))return true;
		else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
		}
		if(gdata.gamesta!=GST_GAMEING && gdata.gamesta!=GST_CONTINUE)return false;	
		if(broteftdone)return false;

		if(dtime>=500)return false;
		float ft=6.0f/500.0f;
		float ft1=(float)ft*(float)dtime;
		int alp=(int)(ft1+0.5f);
		
		DrawOBB(eft->ort,1+alp,false);
		return true;
	}
	bool looprotani(Eftstr *eft)
	{
		unsigned int dtime=gettimetick()-eft->dtime;
		if(eft->lagtime)
		{ if(((dtime/1000) <eft->lagtime ))return true;
		else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
		}
		if(gdata.gamesta!=GST_GAMEING && gdata.gamesta!=GST_CONTINUE)return false;	
		
		if(dtime>1000)
		{
			Rot(eft->prt[0],eft->prt[1], (eft->prt[2]>0)?0:1 );
			SetRot(eft->prt[0],eft->prt[1],0);
			broteftdone=true;
			broting=false;
			if(eft->bcontinue==true && eft->prt[3]>0)
			{
				startrot(rand()%3,rand()%gdata.magcubsize, ((rand()%2==0)?-1:1) ,eft->prt[3]-1,true);
			}
			return false;
		}
		float ft=90.0f/1000.0f;
		float dg=(float)dtime * ft;
		SetRot(eft->prt[0],eft->prt[1],dg*eft->prt[2]);
//		if( (dtime)%100 > 1)
		{
			startrot1(eft->prt[0],eft->prt[1],dg*eft->prt[2]);
		}

		return true;
	}
	void startxumuani()
	{
		Eftstr *estr=new Eftstr;
		if(estr==NULL){fals+=1;return;};
		news+=1;
		estr->Eftp=EFT_XUMU;
		estr->dtime=gettimetick();
		estr->lagtime=0;
		estr->ort=ORECT(Point3(0,0,0),Point3(50,50,50));
		Eftlst.Push(estr);
	};
	void startxumu2()
	{
		Eftstr *estr=new Eftstr;
		if(estr==NULL){fals+=1;return;};
		news+=1;
		estr->Eftp=EFT_XUMU2;
		estr->dtime=gettimetick();
		estr->lagtime=0;
		Eftlst.Push(estr);

		for(int i=0;i<WW*HH;i++)
			part[i].init();
		phand=ptmag.makeplangrid(Point3(0,0,0),100,1);
		ppc=ptmag.getptcpoint(phand);
		for( i=0;i<WW;i++)
			ppc[i].s0.x*=2.50f;
	}
	bool loopxumuani2(Eftstr *eft)
	{
		unsigned int dtime=gettimetick()-eft->dtime;
		if(eft->lagtime)
		{ if(((dtime/1000) <eft->lagtime ))return true;
		else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
		}
		if(gdata.gamesta!=GST_XUMU)
			return false;
		if(dtime>13000)
		{
			startxumu2();
			return false;
		}
		else if(dtime>10000)
		{

		}
		else if(dtime>1500)
		{	
			ptmag.run(phand);
			print_char(ppc[0].s.x+210,ppc[0].s.y+72,'M',2);
			print_char(ppc[1].s.x+210,ppc[1].s.y+72,'a',2);
			print_char(ppc[2].s.x+210,ppc[2].s.y+72,'g',2);
			print_char(ppc[3].s.x+210,ppc[3].s.y+72,'i',2);
			print_char(ppc[4].s.x+210,ppc[4].s.y+72,'c',2);
			print_char(ppc[5].s.x+210,ppc[5].s.y+72,'C',2);
			print_char(ppc[6].s.x+210,ppc[6].s.y+72,'u',2);
			print_char(ppc[7].s.x+210,ppc[7].s.y+72,'b',2);
			print_char(ppc[8].s.x+210,ppc[8].s.y+72,'e',2);
			print_char(ppc[9].s.x+210,ppc[9].s.y+72,'3',2);
			print_char(ppc[10].s.x+210,ppc[10].s.y+72,'D',2);
		}
		if(dtime<10000)
		{
			line(150,82, 254,82,4);
		}
		return true;
	};
	bool loopxumuani1(Eftstr *eft)
	{
		unsigned int dtime=gettimetick()-eft->dtime;
		if(eft->lagtime)
		{ if(((dtime/1000) <eft->lagtime ))return true;
		else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
		}
		if(gdata.gamesta!=GST_XUMU)return false;

		int alp=(dtime/100)%10;
		if(alp>6)return false;

		eft->ort.Extent=eft->ort.Extent*1.04;
		eft->ort.Center=eft->ort.Center+eft->ps;
		DrawOBB(eft->ort,1+alp,false);
		return true;
	}
	bool loopxumuani(Eftstr *eft)
	{
		unsigned int dtime=gettimetick()-eft->dtime;
		if(eft->lagtime)
		{ if(((dtime/1000) <eft->lagtime ))return true;
		else { eft->dtime=gettimetick();eft->lagtime=0;return true;}
		}
		if(gdata.gamesta!=GST_XUMU)
		{
			acting=false;
			return false;
		}

		eft->ort.SetPYR(0,5,0);
		DrawOBB(eft->ort,1+rand()%9*7,false);
//		print_string(150,80,2,"MagicCube3D");
//		line(150,90, 236,90,2);
		if(dtime%10==(dtime/10)%10)
		{
			Eftstr *estr=new Eftstr;
			if(estr==NULL){fals+=1;};
			news+=1;
			estr->Eftp=EFT_XUMU1;
			estr->dtime=gettimetick();
			estr->lagtime=3;
			estr->ort=eft->ort;
			estr->ps=eft->ort.Axis[2];//Point3((rand()%30-rand()%30),0,(rand()%30-rand()%30));
			Eftlst.Push(estr);
		}
		return true;
	};
	void Effectdestroy();

	void startloseani(char pl);

	bool looploseani(Eftstr *eft);
	void RenderUI()
	{
		m_smallwindlg.OnRender(GetTickCount());
		m_helpdlg.OnRender(GetTickCount());

		if(m_helpdlg.GetVisible())
		{
			print_string(120,170,30,"Designer: Jason B");
			print_string(120,186,30,"Supervisor: Michi Zhu");

			print_string(120,40,30,"Keyboard Ctrl:");
			print_string(140,60,30,"<BackUp> <R> <SPACE>");
			print_string(140,70,30,"<UP> <DOWN>");
			print_string(120,100,30,"Mouse Ctrl:");
			print_string(140,120,30,"All Btn Used");

		}
		POINT pt;	m_smallwindlg.GetLocation(pt);
		
//		RD->SysCamera->p=RD->SysCamera->p*-1;
		Vector3 vc1,vc;
		vc=vc1=RD->SysCamera->p;
		vc.Unit();	RD->SysCamera->p=vc*-1500;
		RD->SysCamera->_u=RD->SysCamera->_u*-1;
		RD->SysCamera->_v=RD->SysCamera->_v*-1;
		if(prjtyp==1)
			RD->SysCamera->vWorldScale=0.08f;
		RD->SetViewPortEx(Point3(pt.x,pt.y+10,0),45,100,100,100, (prjtyp==0)?PRJ_PERS:PRJ_PARALL);


//		RD->SysCamera->LookAt(Point3(0,0,1500),Vector3(0,0,1),Vector3(0,1,0));
		if(m_smallwindlg.GetMinimized()==false)
		{
			for(int i=0;i<gdata.magcubsize*gdata.magcubsize*gdata.magcubsize;i++)
				m_unit[i].Draw();
		}
		if(prjtyp==1)
			RD->SysCamera->vWorldScale=0.14f;
		RD->SysCamera->p=vc1;
		RD->SysCamera->_u=RD->SysCamera->_u*-1;
		RD->SysCamera->_v=RD->SysCamera->_v*-1;
		RD->SetViewPortEx(Point3(0,0,0),90,WIDTH,HEIGHT,WIDTH,(prjtyp==0)?PRJ_PERS:PRJ_PARALL);

		
//		RD->SysCamera->LookAt(Point3(0,0,-1500),Vector3(0,0,1),Vector3(0,1,0));
	};
	void MsgProcUI(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		m_smallwindlg.MsgProc(hwnd,iMsg,wParam,lParam);
	//	m_helpdlg.MsgProc(hwnd,iMsg,wParam,lParam);
	};
	void InitUI()
	{
		m_smallwindlg.SetLocation(282,20);
		m_smallwindlg.SetSize(100,100);
		m_smallwindlg.SetCaptionHeight(10);
		m_smallwindlg.EnableCaption(true);
		m_smallwindlg.SetCaptionText("Mirror");

		m_helpdlg.SetLocation(100,20);
		m_helpdlg.SetSize(200,200);
		m_helpdlg.SetCaptionHeight(10);
		m_helpdlg.EnableCaption(true);
		m_helpdlg.SetCaptionText("Help");
		m_helpdlg.SetVisible(false);
	};
	void DrawXumu()
	{
		int tm=(gettimetick()/700)%2;
		print_string(120,240,tm*2,"Press Enter to skip",0);
	};
	void DrawCubcood()
	{
		Point3 tt,tt0,tt1;
		tt0=Point3(-400,-300,1000)*RD->SysCamera->WordMat;
		DrawCoord(tt0,Point3(1,0,0),Point3(0,1,0),Point3(0,0,1));
		tt1=Rasterize(tt0);
		tt=Rasterize(Point3(1,0,0)*52+tt0);
		print_char(tt.x,tt.y,'X',2);
		tt=Rasterize(Point3(0,1,0)*52+tt0);
		print_char(tt.x,tt.y,'Y',2);
		tt=Rasterize(Point3(0,0,1)*52+tt0);
		print_char(tt.x,tt.y,'Z',2);
	};
	void DrawCub()
	{
		ORECT _ort;CubeUnit *cu;
		for(int i=0;i<gdata.magcubsize*gdata.magcubsize*gdata.magcubsize;i++)
		{
			m_unit[i].Draw();

/*			cu=&m_unit[i];
			_ort=ORECT(cu->pos,Point3(UNITSIZE/2,UNITSIZE/2,UNITSIZE/2));
			_ort.SetAxis(cu->xyz[0],cu->xyz[1],cu->xyz[2]);
			DrawOBB(_ort,2,true);
*/
		}
	};
	void initdevice()
	{
		DefInit3D();
		RD=GetRenderDev();
		ptmag.createptcs(part,WW*HH,P_GRID);
		ptmag.setsegment(WW,HH);
		
	};
	void gamestart()
	{
		m_step=0;
		int ix,iy,iz;
		for(iz=0;iz<gdata.magcubsize;iz++)
		{
			for(iy=0;iy<gdata.magcubsize;iy++)
			{
				for(ix=0;ix<gdata.magcubsize;ix++)
				{
					//m_unit[iz*magcubsize*magcubsize +iy*magcubsize+ix].SetPos(
					//	ix*100-ps.x,iy*100-ps.y,iz*100-ps.z);
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].Init();
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].SetGamedata(&gdata);
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].SetPosByUnit(ix,iy,iz);
					m_unit[iz*gdata.magcubsize*gdata.magcubsize +iy*gdata.magcubsize+ix].SetShow(false);
				}
			}
		}
		for(int i=0;i<_DMAX;i++)
			SetShow((_DERECTION)i,true);

		SetColor(_L,2);
		SetColor(_F,15);
		SetColor(_R,22);
		SetColor(_B,30);
		SetColor(_U,10);
		SetColor(_D,38);
		if(prjtyp==0)
		{
			RD->SysCamera->vWorldScale=1;
			RD->SetViewPortEx(Point3(0,0,0),90,WIDTH,HEIGHT,WIDTH,PRJ_PERS);
		}
		else 
		{
			RD->SysCamera->vWorldScale=0.14f;
			RD->SetViewPortEx(Point3(0,0,0),90,WIDTH,HEIGHT,WIDTH,PRJ_PARALL);
		}
		RD->SetViewPortEx(Point3(0,0,0),90,WIDTH,HEIGHT,WIDTH,(prjtyp==0)?PRJ_PERS:PRJ_PARALL);
		RD->SysCamera->LookAt(Point3(0,0,-1500),Vector3(0,0,1),Vector3(0,1,0));
//		startrot(rand()%3,rand()%gdata.magcubsize, ((rand()%2==0)?-1:1) ,gdata.magcubsize*2,true);
		startwinani();
	};
public:
	CubeUnit m_unit[20*20*20];
	UIDialog m_smallwindlg,m_helpdlg;
	NODE<Eftstr *> Eftlst;
	int m_score;
	int m_time;
	int m_step;
	_gamedata gdata;//公用信息
	BLTList<RotStep> m_StepList;
	int prjtyp;
	int cubesize;
	int m_currentdir;//当前鼠标点选面
	Point3 m_currentpos;//当前鼠标点选单元坐标
	bool broting,broteftdone,acting;
	ptc part[WW*HH],*ppc;
	particlsys ptmag;
	int phand;
	int tiping,tiptime;
private:
};


CameraList cmlst;
CubeUnit cut;

void MagicCube3D::Init()
{

//	cmlst.AddCamera(RD->SysCamera);
//	cmlst.SetCurCam(0);
//	cmlst.SetMovement2(Point3(0,0,0),1000,500);

//	cm.init(45,100,100,100);
//	cm.Position(Point3(0,0,200));
	freealleft();
	gdata.init();

	RD->SetViewPortEx(Point3(0,0,0),90,WIDTH,HEIGHT,WIDTH,(prjtyp==0)?PRJ_PERS:PRJ_PARALL);
	RD->SysCamera->LookAt(Point3(0,500,-1500),Vector3(0,-0.35f,1),Vector3(0,1,0));
	InitUI();

	cubesize=1;
	prjtyp=0;
	m_score=0;
	m_time=0;
	m_step=0;
	m_currentpos=Point3(0,0,0);
	m_currentdir=_DMAX;
	broting=false;
	broteftdone=true;
	tiping=0;
	tiptime=0;
	acting=false;

	Vector3 ps=Vector3(100,100,100);//UNITSIZE*magcubsize,UNITSIZE*magcubsize,UNITSIZE*magcubsize);



	startxumuani();
	startxumu2();
}
int m_xx=-1,m_dir=-1;
void MagicCube3D::Loop()
{
//	DrawCoord(Point3(0,0,0),Point3(1,0,0),Point3(0,1,0),Point3(0,0,1));
	DrawBk();
	if(gdata.gamesta==GST_XUMU)
	{

		DrawXumu();
		if(getkey(VK_SPACE,true) || getkey(VK_RETURN,true))
			gdata.gamesta=GST_MNU;
		Effectloop();
	}
	else if(gdata.gamesta==GST_MNU)
	{
		DrawMenu();
		if(getkey(VK_ADD,true))
		{
			if(gdata.magcubsize<19)gdata.magcubsize+=1;
		}
		else if(getkey(VK_SUBTRACT,true))
		{
			if(gdata.magcubsize>1)gdata.magcubsize-=1;
		}	

	}
	else if(gdata.gamesta==GST_GAMEING)
	{
		Drawscore();
		DrawCubcood();
		//	cmlst.RunMoveMent();
//		print_num(200,200,_obite,2);
//		print_num(220,200,_floor,2);
//		print_num(240,200,_dir,2);
		//	CheckShow();
//		DrawCoord(Point3(0,0,0),Point3(1,0,0),Point3(0,1,0),Point3(0,0,1));
		if(tiping==1)
		{
			print_string(100,40,2,"Pls Drag Mouse for turning");
			if( (GetTickCount()-tiptime)>1000)
			{
				tiping=0;
				tiptime=0;
			}
		}
		
		if(getkey('R',true))
			startrot(rand()%3,rand()%gdata.magcubsize, ((rand()%2==0)?-1:1) ,gdata.magcubsize*2,true);
		else if(getkey(VK_ESCAPE,true))
			gdata.gamesta=GST_CONTINUE;
		else if(getkey(VK_SPACE,true))
		{
			RD->SysCamera->LookAt(Point3(0,0,-1500),Vector3(0,0,1),Vector3(0,1,0));
		}
		else if(getkey(VK_BACK,true))
		{
			int num=m_StepList.Entries()-1;
			if(num>=0 && broting==false &&broteftdone==true)
			{
				RotStep *rt;
				rt=m_StepList[num];
				startrot((*rt)[0],(*rt)[1],(*rt)[2]*-1);
				m_StepList.Remove(num);
			}
		}
/*
				else if(getkey('S',true))
				{
					Quat sqt=Quat(Vector3(0,0,1),45.0f *Pi);
					Quat dqt=Quat(Vector3(0,0,0),0.0f *Pi);
					startrotv(dqt,RD->SysCamera->quatw,2000);//sqt
				}*/
		


		DrawCub();
		RenderUI();
		if(getkey('Q',true))
			startwinani();
		RD->SysCamera->TransefCameraByKey(false);

		Effectloop();
	}	
	else if(gdata.gamesta==GST_CONTINUE)
	{
		print_string(120,130,2,"CONTINUE GAME?  Y/N");
		if(getkey('Y',true))
			gdata.gamesta=GST_GAMEING;
		else if(getkey('N',true)){
			{
				gdata.gamesta=GST_XUMU;
				Init();
			}
		}
	}



}
void MagicCube3D::Destroy()
{

}




MagicCube3D magiccube;
static int _speed=0,_frames=0,_fps=0;
static int mmkeys=500,mmgams=500;
void DoFrame();
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR szCmdLine, int iCmdShow){
	MSG	msg;
	magiccube.initdevice();
	magiccube.Init();

	if(!_m_buf.InitWindow(WIDTH, HEIGHT, "GEngin  - MagicCube3D", hInstance, &hWnd, WndProc, NULL)) return FALSE;
	if(!_m_buf.SetBufferMode(WIDTH, HEIGHT, BPP, FullScreen, &tcf)) return FALSE;

	char ct=1;
	lineclr(255,0,0,  0,0,0,  ct+0*7, ct+1*7);
	lineclr(255,255,0, 0,0,0,  ct+1*7, ct+2*7);
	lineclr(0,0,255,  0,0,0,  ct+2*7, ct+3*7);
	lineclr(0,255,0,  0,0,0,  ct+3*7, ct+4*7);
	lineclr(255,255,255, 0,0,0, ct+4*7, ct+5*7);
	lineclr(255,177,88, 0,0,0, ct+5*7, ct+6*7);
	lineclr(255,0,255, 0,0,0,  ct+6*7, ct+7*7);
	lineclr(88,177,255, 0,0,0, ct+7*7, ct+8*7);
	lineclr(0,255,255, 0,0,0,  ct+8*7, ct+9*7);
	
	float dtime;
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!GetMessage(&msg, NULL, 0, 0)){
				return msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(_fps<mmgams)
		{
			if(IsMinimized == FALSE && (ActiveApp && !FullScreen))
			{
				_speed=GetTickCount();
				//				if(_delay(mmgams))
				DoFrame();
				dtime=(float)(GetTickCount()-_speed);
				if(dtime==0)dtime=0.01f;
				_fps=1000.0f/dtime;
			}
			else{	WaitMessage();	}
		}
		else
		{
			dtime=(float)(GetTickCount()-_speed);
			if(dtime==0)dtime=0.01f;
			_fps=1000.0f/dtime;
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
	
	if(_m_buf.Lock(&_m_bd))
	{
		clearscr();

		magiccube.Loop();


		
		drawfps();
		_m_buf.Unlock();
	}		
	fps=gettimetick();
	_m_buf.UpdateFrontBuffer(FullScreen ? NULL : UFB_STRETCH);	//Call UpdateFrontBuffer while UNLOCKED.
}
static bool bvis=true;
static bool suc=true;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	magiccube.MsgProcUI(hwnd,iMsg,wParam,lParam);
	switch(iMsg){
		case WM_ACTIVATEAPP :
			ActiveApp = wParam;
			break;
		case WM_ACTIVATE :
			IsMinimized = HIWORD(wParam);
			break;
		case WM_CREATE :
			return 0;
		case WM_LBUTTONDOWN:
			{
				MouseX=LOWORD(lParam);
				MouseY=HIWORD(lParam);
				lmclked=true;
				if(magiccube.gdata.gamesta!=GST_GAMEING)break;
				suc=magiccube.Getselcubeinfo();
			}
			break;
		case WM_LBUTTONUP:
			{
				mx= LOWORD(lParam);
				my= HIWORD(lParam);
				if(magiccube.gdata.gamesta!=GST_GAMEING)break;
				if(suc)magiccube.GetOpr();
				lmclked=false;
			}
			break;
		case WM_RBUTTONDOWN:
			omx=mx=MouseX = LOWORD(lParam);
			omy=my=MouseY = HIWORD(lParam);

			rmclked=true;
			break;
		case WM_RBUTTONUP:rmclked=false;break;
		case WM_MOUSEWHEEL:
			{			
				if(magiccube.gdata.gamesta!=GST_GAMEING)break;
				Camera *cm=RD->SysCamera;
				if (HIWORD(wParam)==120)
				{
					if(wheeln>=9)wheeln=9;
					else
					{
						wheeln+=1;						
						cm->p=cm->p+cm->_n*100;
						cm->GetCameraSpaceMat();
						
					}
				}
				else
				{
					if(wheeln<=0)wheeln=0;
					else
					{
						wheeln-=1;
						cm->p=cm->p+cm->_n*-100;
						cm->GetCameraSpaceMat();
					}
				}
			}
			break;
		case WM_MOUSEMOVE :
			mx= LOWORD(lParam);
			my= HIWORD(lParam);
			if(rmclked)
			{	
				//RD->SysCamera->TransefCameraByMouse(mx-MouseX,my-MouseY,false);
				if(magiccube.gdata.gamesta==GST_GAMEING)
					RD->SysCamera->TransefCameraByMouse1( (mx-omx)*100,(my-omy)*100);
			}
			omx=mx;omy=my;
			break;
		case WM_KEYDOWN :
			_m_wparam=wParam;
			switch(wParam){
				case VK_ESCAPE :
		//			PostMessage(hwnd, WM_CLOSE, NULL, NULL);
					break;
				case VK_RETURN:
					break;
				case VK_F1:
					magiccube.m_helpdlg.SetVisible(!magiccube.m_helpdlg.GetVisible());
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






















