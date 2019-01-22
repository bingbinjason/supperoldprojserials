
#pragma once

#include "core.h"
#include "core01.h"
#include "core02.h"
#include "core04.h"
#include "core06.h"
#include "core07.h"


#include "carsystem/Curve.h"
#include "carsystem/Wheel.h"
#include "carSystem/CarLoader.h"
#include "carsystem/misc.h"

#include "carsystem//Game.h"
#include "carsystem//WorldModel.h"
#include "carsystem//Car.h"

#include "tinyxml/tinyxml.h"
#include <math.h>
#include <vector>

int news=0,dels=0,fals=0;
static INT64 _speed=0,_fps=1000;
static int mmkeys=10,mmgams=0;
float m_fps=0;

bool pause=true;

#define _DEBUG_ON_RELEASE









#define _MAX_GEAES 10
class Traction
{
public:
	Traction()
	{
		reset();
	};
	void load()
	{
		//Audi 
		ig[1]=3.5f;//2.315;
		ig[2]=2.2f;//1.944;
		ig[3]=1.5f;//1.308;
		ig[4]=1.1f;//1.029;
		ig[5]=0.9f;//0.837;

		i0=4.1f;//1;
		wheelrad=0.3f;
		transmissonef=0.9f;//1;
		rollfriction=0.010f;
		A=2.09f;
		p=1.2258f;//空气密度
		Cd=0.30f;
		weight=1280;
		created=false;
	};
	void reset()
	{
		A=0;p=0;
		rollfriction=0;
		for(int i=0;i<_MAX_GEAES;i++)
		{
			ig[i]=0;
			maxua[i]=0;
			maxft[i]=0;
			tractioncrv[i].reset();
		}
		weight=0;
		Cd=0;
		i0=0;
		wheelrad=0.3f;
		transmissonef=1;
		created=false;
	};
	void create(Curve *torquecrv,int gears=5)
	{
		if(torquecrv->isEmpty())return;
		float cvt=0.377f;

		float maxrpm=8000;
		for(int gear=1;gear<=gears;gear++)
		{
			float igi0=ig[gear]*i0;

			maxua[gear]=cvt*wheelrad*maxrpm/(igi0);

			for(float rpm=0;rpm<maxrpm;rpm+=200)
			{
				float tq=torquecrv->getValue(rpm);

				float ft= (tq*igi0*transmissonef)/wheelrad;
				float ua=cvt*wheelrad*rpm/(igi0);
				tractioncrv[gear].addPoint(ua,ft);

				if(maxft[gear]<ft)
					maxft[gear]=ft;
			}
		}
		for(float ua=0;ua<=220;ua+=10)
		{
			float cvt=1.0f/21.15f;
			float fw=(Cd*A*ua*ua)*cvt;//风阻
			float fr=weight*9.8f*rollfriction;//滚阻 //weight的单位是公斤，1公斤=9.8=10N
			float f=fw+fr;
			AeroRollcrv.addPoint(ua,f);
		}
		created=true;
	};
	void reCreate(Curve *torquecrv,int gears=5)
	{
		//load();
		for(int i=0;i<_MAX_GEAES;i++)
		{
			tractioncrv[i].reset();
		}
		AeroRollcrv.reset();

		created=false;
		create(torquecrv,gears);
	};
	bool isCreated(){return created;};
	float getMaxUa(int gear){return maxua[gear];};
	float getMaxFt(int gear){return maxft[gear];};
	float getValue(int gear,float ua)
	{
		return tractioncrv[gear].getValue(ua);
	};
	float getARValue(float ua)
	{
		return AeroRollcrv.getValue(ua);
	};
public:
	float ig[_MAX_GEAES],i0;
	float rollfriction;//滚动摩擦
	float A,Cd,p;//空气阻力
	float wheelrad;
	float weight;//重量
	float transmissonef;//传动效率
	float maxua[_MAX_GEAES];//最大车速
	float maxft[_MAX_GEAES];//最大驱动力
	Curve tractioncrv[_MAX_GEAES];//驱动力曲线
	Curve AeroRollcrv;//空阻+滚阻曲线
	bool created;
};








enum{AXIS2=0,AXIS4,NONE,};
enum{PACEJKA=0,TRACTION,CURVE,TORQUE,GEARS,WHEELSUS,WEIGHTDIST,TRANSMISS,ASSIST,MAPEDIT};
class VehicleEdit
{
public:

	VehicleEdit()
	{
//		setAxisType(AXIS2);
//		UnitX=1;
//		UnitY=1;
//		AxisScale=1;
//		MaxAxisX=100;
//		MaxAxisY=100;
		editing=false;
		selpoint=-1;
		torqueconsumption=0;//0,torque, 1,consumption
		powerscale=1.18f;

		setAxisX(200,50);
		setAxisY(200,50);
		setAxisScale(1,1);
		setEditMode(PACEJKA);


		b[0].Init("b0",		 0		,	2.0		,&pacejka.b0	,	"shape factor" );
		b[1].Init("b1",		 -25	,	25		,&pacejka.b1	,	"load infl. on long. friction coef" );
		b[2].Init("b2",		 0		,	3000	,&pacejka.b2	,	"long. friction coef at load=");
		b[3].Init("b3",		 -1		,	1		,&pacejka.b3	,	"curvature factor of stiffness");
		b[4].Init("b4",		 0		,	500		,&pacejka.b4	,	"change of stiffness with load at load=");
		b[5].Init("b5",		 -1		,	1		,&pacejka.b5	,	"change of progressivity of stiffness/load");
		b[6].Init("b6",		 -1		,	1		,&pacejka.b6	,	"curvature change with load^2");
		b[7].Init("b7",		 -1		,	1		,&pacejka.b7	,	"cuvature change with load");
		b[8].Init("b8",		 -1		,	1		,&pacejka.b8	,	"curvature at load=0");
		b[9].Init("b9",		 -1		,	1		,&pacejka.b9	,	"load influence on hor. shift(%/KN)");
		b[10].Init("b10",	 -1		,	1		,&pacejka.b10	,	"horizontal shift at load = 0 (%)");
		b[11].Init("b11",    -1		,	1		,&pacejka.b11	,	"load influence on vertical shift (N/kN)");
		b[12].Init("b12",	 -1		,	1		,&pacejka.b12	,	"vertical shift at load=0 (N)");


		a[0].Init("a0",		 0		,	2		,&pacejka.a0	,	"shape factor");
		a[1].Init("a1",		 -50	,	50		,&pacejka.a1	,	"load infl. on lat. friction coeff (*1000) (kN^-1)");
		a[2].Init("a2",		 0		,	3000	,&pacejka.a2	,	"lateral friction coef at load=0 (*1000)");
		a[3].Init("a3",		 0		,	3000	,&pacejka.a3	,	"maximum stiffnes (N/deg)");
		a[4].Init("a4",		 0		,	50		,&pacejka.a4	,	"load at maximum stiffness (kN)");
		a[5].Init("a5",		 -1		,	1		,&pacejka.a5	,	"camber influence on stiffnes");
		a[6].Init("a6",		 -2.5	,	2.5		,&pacejka.a6	,	"curvature change with load");
		a[7].Init("a7",		 -2.5	,	2.5		,&pacejka.a7	,	"curvature at load=0");
		a[8].Init("a8",		 -1		,	1		,&pacejka.a8	,	"hor. shift because of camber (deg/deg)");
		a[9].Init("a9",		 -1		,	1		,&pacejka.a9	,	"load influence on horizontal shift (deg/kN)");
		a[10].Init("a10",	 -1		,	1		,&pacejka.a10	,	"horizontal shift at load=0 (deg)");
		a[11].Init("a111",	 -15	,	15		,&pacejka.a111	,	"camber influence on vertical shift , load dependent (N/deg/kN)");
		a[12].Init("a112",	 -1		,	1		,&pacejka.a112	,	"camber influence on vertical shift (N/deg/kN^2)");
		a[13].Init("a12",	 -10	,	10		,&pacejka.a12	,	"load influence on vertical shift (N/kN)");
		a[14].Init("a13",	 0		,	100		,&pacejka.a13	,	"vertical shift at load=0 (N)");


		c[0].Init("c0",		 -2.5	,	2.5		,&pacejka.c0,	"shape factor");
		c[1].Init("c1",		 -5		,	5		,&pacejka.c1,	"load influence of peak value (Nm/kN^2)");
		c[2].Init("c2",		 -15	,	15		,&pacejka.c2,	"load influence of peak value (Nm/kN)");
		c[3].Init("c3",		 -1.5	,	1.5		,&pacejka.c3,	"curvature factor of stiffness (m/deg/kN^2)");
		c[4].Init("c4",		 -10	,	10		,&pacejka.c4,	"change of stiffness with load at load=0 (Nm/deg/kN)");
		c[5].Init("c5",		 -1		,	1		,&pacejka.c5,	"change of progressivity of stiffness/load (kN^-1)");
		c[6].Init("c6",		 -1		,	1		,&pacejka.c6,	"camber influence on stiffness (%/deg/100)");
		c[7].Init("c7",		 -1		,	1		,&pacejka.c7,	"curvature change with load^2");
		c[8].Init("c8",		 -7.5	,	7.5		,&pacejka.c8,	"(non-dimensional)");
		c[9].Init("c9",	     -25	,	25		,&pacejka.c9,	"curvature at load =0");
		c[10].Init("c10",	 -1		,	1		,&pacejka.c10,	"camber influence on stiffness");
		c[11].Init("c11",	 -0.5	,	0.5		,&pacejka.c11,	"camber influence on horizontal shift (deg/deg)");
		c[12].Init("c12",	 -0.5	,	0.5		,&pacejka.c12,	"load influence on horizontal shift (deg/kN)");
		c[13].Init("c13",	 -1		,	1		,&pacejka.c13,	"horizontal shift at load =0 (deg)");
		c[14].Init("c14",	 -1		,	1		,&pacejka.c14,	"camber influence on vertical shift (Nm/deg/kN^2)");
		c[15].Init("c15",	 -2.5	,	2.5		,&pacejka.c15,	"camber influence on vertical shift (Nm/deg/kN)");
		c[16].Init("c16",	 -1.5	,	1.5		,&pacejka.c16,	"load influence on vertical shift (Nm/kN)");
		c[17].Init("c17",	 -2.5	,	2.5		,&pacejka.c17,	"vertical shift at load=0 (Nm)");

		ig0.Init("I0", -15 , 15 , &traction.i0, "total reduction ratio");
		ig[1].Init("Ig1", -15 , 15 , &traction.ig[1], "gear1 ratio");
		ig[2].Init("Ig2", -15 , 15 , &traction.ig[2], "gear2 ratio");
		ig[3].Init("Ig3", -15 , 15 , &traction.ig[3], "gear3 ratio");
		ig[4].Init("Ig4", -15 , 15 , &traction.ig[4], "gear4 ratio");
		ig[5].Init("Ig5", -15 , 15 , &traction.ig[5], "gear5 ratio");
		transmissionef.Init("efc",0 , 1 , &traction.transmissonef, "transmission efc");
		A.Init("A", 0 , 5 ,&traction.A , "aero coef");
		wheelrad.Init("wheelr", 0,1, &traction.wheelrad, "wheel radius");
		rollcoef.Init("rollc", 0, 1, &traction.rollfriction, "wheel rolling coef");
		Cd.Init("Cd",0,1, &traction.Cd, "aero coef");
		weight.Init("G", 500,5000, &traction.weight, "vehicle weight");


		float v;
		//wheel,suspension
		wheelposfl[0].Init("x",-10,10,&carDef.wheelPos[0][0],"Position-X");
		wheelposfl[1].Init("y",-10,10,&carDef.wheelPos[0][1],"Position-Y");
		wheelposfl[2].Init("z",-10,10,&carDef.wheelPos[0][2],"Position-Z");

		wheelposfr[0].Init("x",-10,10,&carDef.wheelPos[1][0],"Position-X");
		wheelposfr[1].Init("y",-10,10,&carDef.wheelPos[1][1],"Position-Y");
		wheelposfr[2].Init("z",-10,10,&carDef.wheelPos[1][2],"Position-Z");

		wheelposrl[0].Init("x",-10,10,&carDef.wheelPos[2][0],"Position-X");
		wheelposrl[1].Init("y",-10,10,&carDef.wheelPos[2][1],"Position-Y");
		wheelposrl[2].Init("z",-10,10,&carDef.wheelPos[2][2],"Position-Z");

		wheelposrr[0].Init("x",-10,10,&carDef.wheelPos[3][0],"Position-X");
		wheelposrr[1].Init("y",-10,10,&carDef.wheelPos[3][1],"Position-Y");
		wheelposrr[2].Init("z",-10,10,&carDef.wheelPos[3][2],"Position-Z");


		wheelsizef[0].Init("Mass",0,100,&carDef.wheelMass[0],"WheelMass");
		wheelsizef[1].Init("Width",0,100,&carDef.wheelWidth[0],"WheelWidth");
		wheelsizef[2].Init("Radius",0,100,&carDef.wheelRadius[0],"WheelRad");

		wheelsizer[0].Init("Mass",0,100,&carDef.wheelMass[1],"WheelMass");
		wheelsizer[1].Init("Width",0,100,&carDef.wheelWidth[1],"WheelWidth");
		wheelsizer[2].Init("Radius",0,100,&carDef.wheelRadius[1],"WheelRad");


		wheeltyref[0].Init("Bounce",0,1000,&carDef.tyreBounce[0],"TyreBounce");
		wheeltyref[1].Init("Friction",0,1000,&carDef.tyreFriction[0],"TyreFriction");
		wheeltyref[2].Init("Rollicoef",0,1000,&carDef.tyreRolliCoef[0],"TyreRollingCoef");

		wheeltyrer[0].Init("Bounce",0,1000,&carDef.tyreBounce[1],"TyreBounce");
		wheeltyrer[1].Init("Friction",0,1000,&carDef.tyreFriction[1],"TyreFriction");
		wheeltyrer[2].Init("Rollicoef",0,1000,&carDef.tyreRolliCoef[1],"TyreRollingCoef");


		susaxisf[0].Init("x",-1,1,&carDef.susAxis[0][0],"Axis-X");
		susaxisf[1].Init("y",-1,1,&carDef.susAxis[0][1],"Axis-Y");
		susaxisf[2].Init("z",-1,1,&carDef.susAxis[0][2],"Axis-Z");

		susaxisr[0].Init("x",-1,1,&carDef.susAxis[1][0],"Axis-X");
		susaxisr[1].Init("y",-1,1,&carDef.susAxis[1][1],"Axis-Y");
		susaxisr[2].Init("z",-1,1,&carDef.susAxis[1][2],"Axis-Z");


		susspringdampf[0].Init("Spring",0,10000,&carDef.susSpring[0],"SuspSpring");
		susspringdampf[1].Init("Damper",0,10000,&carDef.susDamper[0],"SuspDamper");

		susspringdampr[0].Init("Spring",0,10000,&carDef.susSpring[1],"SuspSpring");
		susspringdampr[1].Init("Damper",0,10000,&carDef.susDamper[1],"SuspDamper");


		susarbf[0].Init("Spring",0,10000,&carDef.antiRollBarSpring[0],"ArbSpring");
		susarbf[1].Init("Damper",0,10000,&carDef.antiRollBarDamper[0],"ArbDamper");

		susarbr[0].Init("Spring",0,10000,&carDef.antiRollBarSpring[1],"ArbSpring");
		susarbr[1].Init("Damper",0,10000,&carDef.antiRollBarDamper[1],"ArbDamper");


		sustoecamber[0].Init("Toe",-1,1,&carDef.toe,"SusToe");
		sustoecamber[1].Init("Camber",-1,1,&carDef.camber,"SusCamber");

		//transmition
		gearchangupdown[0].Init("ChangeUp",1000,4000,&carDef.autoUp,"ChangeUp");
		gearchangupdown[1].Init("ChangeDown",1000,4000,&carDef.autoDown,"ChangeDown");
	
		tramtractiondiff[0].Init("PowerBias",0,1,&carDef.powerBias,"PowerBias");
		tramtractiondiff[1].Init("LockRatio",0,1,&carDef.lockRatio,"LockRatio");

		tramclutch[0].Init("AutoClutchBrakeRatio",0,1,&carDef.autoClutchBrakeRatio,"AutoClutchBrakeRatio");
		tramclutch[1].Init("ClutchTime",0,2000,&carDef.clutchTime,"ClutchTime");
		tramclutch[2].Init("DeClutchTime",0,2000,&carDef.declutchTime,"DeClutchTime");

		bsbrake[0].Init("HandBrakeRatio",0,1,&carDef.handBrakeRatio,"HandBrakeRatio");
		bsbrake[1].Init("BrakeBias",0,1,&carDef.brakeBias,"BrakeBias");
		bsbrake[2].Init("FrictionKv",0,1,&carDef.brakeFrictionKv,"FrictionKv");

		bssteer[0].Init("LockAngel",0,180,&carDef.steerlockAngel,"LockAngel");

		//assist
		steeringwheel[0].Init("Speed",0,10,&carDef.steeringWheelSpd,"Speed");
		steeringwheel[1].Init("ReturnSpeed",0,10,&carDef.steeringWheelRetSpd,"ReturnSpeed");
		steeringwheel[2].Init("Distance",0,100,&carDef.steeringWheelDist,"Distance");

		throttle[0].Init("Speed",0,10,&carDef.throttlePadelSpd,"Speed");
		throttle[1].Init("ReturnSpeed",0,10,&carDef.throttlePadelRetSpd,"ReturnSpeed");
		throttle[2].Init("Distance",0,100,&carDef.throttlePadelDist,"Distance");

		brake[0].Init("Speed",0,10,&carDef.brakePadelSpd,"Speed");
		brake[1].Init("ReturnSpeed",0,10,&carDef.brakePadelRetSpd,"ReturnSpeed");
		brake[2].Init("Distance",0,100,&carDef.brakePadelDist,"Distance");

		clutch[0].Init("Speed",0,10,&carDef.clutchPadelSpd,"Speed");
		clutch[1].Init("ReturnSpeed",0,10,&carDef.clutchPadelRetSpd,"ReturnSpeed");
		clutch[2].Init("Distance",0,100,&carDef.clutchPadelDist	,"Distance");

		camera0[0].Init("x",0,10,&carDef.cameraPos[0][0],"CamPosX");
		camera0[1].Init("y",0,10,&carDef.cameraPos[0][1],"CamPosY");
		camera0[2].Init("z",0,10,&carDef.cameraPos[0][2],"CamPosZ");
		camera0[3].Init("x",0,10,&carDef.cameraDir[0][0],"CamDirX");
		camera0[4].Init("y",0,10,&carDef.cameraDir[0][1],"CamDirY");
		camera0[5].Init("z",0,10,&carDef.cameraDir[0][2],"CamDirZ");

		camera1[0].Init("x",0,10,&carDef.cameraPos[1][0],"CamPosX");
		camera1[1].Init("y",0,10,&carDef.cameraPos[1][1],"CamPosY");
		camera1[2].Init("z",0,10,&carDef.cameraPos[1][2],"CamPosZ");
		camera1[3].Init("x",0,10,&carDef.cameraDir[1][0],"CamDirX");
		camera1[4].Init("y",0,10,&carDef.cameraDir[1][1],"CamDirY");
		camera1[5].Init("z",0,10,&carDef.cameraDir[1][2],"CamDirZ");

		camera2[0].Init("x",0,10,&carDef.cameraPos[2][0],"CamPosX");
		camera2[1].Init("y",0,10,&carDef.cameraPos[2][1],"CamPosY");
		camera2[2].Init("z",0,10,&carDef.cameraPos[2][2],"CamPosZ");
		camera2[3].Init("x",0,10,&carDef.cameraDir[2][0],"CamDirX");
		camera2[4].Init("y",0,10,&carDef.cameraDir[2][1],"CamDirY");
		camera2[5].Init("z",0,10,&carDef.cameraDir[2][2],"CamDirZ");

		camera3[0].Init("x",0,10,&carDef.cameraPos[3][0],"CamPosX");
		camera3[1].Init("y",0,10,&carDef.cameraPos[3][1],"CamPosY");
		camera3[2].Init("z",0,10,&carDef.cameraPos[3][2],"CamPosZ");
		camera3[3].Init("x",0,10,&carDef.cameraDir[3][0],"CamDirX");
		camera3[4].Init("y",0,10,&carDef.cameraDir[3][1],"CamDirY");
		camera3[5].Init("z",0,10,&carDef.cameraDir[3][2],"CamDirZ");

		camera4[0].Init("x",0,10,&carDef.cameraPos[4][0],"CamPosX");
		camera4[1].Init("y",0,10,&carDef.cameraPos[4][1],"CamPosY");
		camera4[2].Init("z",0,10,&carDef.cameraPos[4][2],"CamPosZ");
		camera4[3].Init("x",0,10,&carDef.cameraDir[4][0],"CamDirX");
		camera4[4].Init("y",0,10,&carDef.cameraDir[4][1],"CamDirY");
		camera4[5].Init("z",0,10,&carDef.cameraDir[4][2],"CamDirZ");

		masspartmain[6].Init("Main",0,1000,&carDef.massPart[0].mass,"Main");
		masspartmain[0].Init("x",-10,10,&carDef.massPart[0].pos[0],"MainPosX");
		masspartmain[1].Init("y",-10,10,&carDef.massPart[0].pos[1],"MainPosY");
		masspartmain[2].Init("z",-10,10,&carDef.massPart[0].pos[2],"MainPosZ");
		masspartmain[3].Init("w",-10,10,&carDef.massPart[0].size[0],"MainWidth");
		masspartmain[4].Init("h",-10,10,&carDef.massPart[0].size[1],"MainHeight");
		masspartmain[5].Init("l",-10,10,&carDef.massPart[0].size[2],"MainLength");


		masspartchassis[6].Init("Chassis",0,1000,&carDef.massPart[1].mass,"Chassis");
		masspartchassis[0].Init("x",-10,10,&carDef.massPart[1].pos[0],"ChassisPosX");
		masspartchassis[1].Init("y",-10,10,&carDef.massPart[1].pos[1],"ChassisPosY");
		masspartchassis[2].Init("z",-10,10,&carDef.massPart[1].pos[2],"ChassisPosZ");
		masspartchassis[3].Init("w",-10,10,&carDef.massPart[1].size[0],"ChassisWidth");
		masspartchassis[4].Init("h",-10,10,&carDef.massPart[1].size[1],"ChassisHeight");
		masspartchassis[5].Init("l",-10,10,&carDef.massPart[1].size[2],"ChassisLength");

		masspartmiddle[6].Init("Middle",0,1000,&carDef.massPart[2].mass,"Middle");
		masspartmiddle[0].Init("x",-10,10,&carDef.massPart[2].pos[0],"MiddlePosX");
		masspartmiddle[1].Init("y",-10,10,&carDef.massPart[2].pos[1],"MiddlePosY");
		masspartmiddle[2].Init("z",-10,10,&carDef.massPart[2].pos[2],"MiddlePosZ");
		masspartmiddle[3].Init("w",-10,10,&carDef.massPart[2].size[0],"MiddleWidth");
		masspartmiddle[4].Init("h",-10,10,&carDef.massPart[2].size[1],"MiddleHeight");
		masspartmiddle[5].Init("l",-10,10,&carDef.massPart[2].size[2],"MiddleLength");

		masspartfront[6].Init("Front",0,1000,&carDef.massPart[3].mass,"Front");
		masspartfront[0].Init("x",-10,10,&carDef.massPart[3].pos[0],"FrontPosX");
		masspartfront[1].Init("y",-10,10,&carDef.massPart[3].pos[1],"FrontPosY");
		masspartfront[2].Init("z",-10,10,&carDef.massPart[3].pos[2],"FrontPosZ");
		masspartfront[3].Init("w",-10,10,&carDef.massPart[3].size[0],"FrontWidth");
		masspartfront[4].Init("h",-10,10,&carDef.massPart[3].size[1],"FrontHeight");
		masspartfront[5].Init("l",-10,10,&carDef.massPart[3].size[2],"FrontLength");

		masspartrear[6].Init("Rear",0,1000,&carDef.massPart[4].mass,"Rear");
		masspartrear[0].Init("x",-10,10,&carDef.massPart[4].pos[0],"RearPosX");
		masspartrear[1].Init("y",-10,10,&carDef.massPart[4].pos[1],"RearPosY");
		masspartrear[2].Init("z",-10,10,&carDef.massPart[4].pos[2],"RearPosZ");
		masspartrear[3].Init("w",-10,10,&carDef.massPart[4].size[0],"RearWidth");
		masspartrear[4].Init("h",-10,10,&carDef.massPart[4].size[1],"RearHeight");
		masspartrear[5].Init("l",-10,10,&carDef.massPart[4].size[2],"RearLength");

		masspartengin[6].Init("Engine",0,1000,&carDef.massPart[5].mass,"Engine");
		masspartengin[0].Init("x",-10,10,&carDef.massPart[5].pos[0],"EnginePosX");
		masspartengin[1].Init("y",-10,10,&carDef.massPart[5].pos[1],"EnginePosY");
		masspartengin[2].Init("z",-10,10,&carDef.massPart[5].pos[2],"EnginePosZ");
		masspartengin[3].Init("w",-10,10,&carDef.massPart[5].size[0],"EngineWidth");
		masspartengin[4].Init("h",-10,10,&carDef.massPart[5].size[1],"EngineHeight");
		masspartengin[5].Init("l",-10,10,&carDef.massPart[5].size[2],"EngineLength");

		//init torque crv , according to Audi V6 3.2FSI发动机
		AddPoint(Vector2(919,230),true);
		AddPoint(Vector2(1240,273),true);
		AddPoint(Vector2(1354,285),true);
		AddPoint(Vector2(1548,291),true);
		AddPoint(Vector2(3000,320),true);
		AddPoint(Vector2(3467,326),true);
		AddPoint(Vector2(5000,317),true);
		AddPoint(Vector2(6000,300),true);
		AddPoint(Vector2(7000,260),true);
		AddPoint(Vector2(7500,230),true);

	};
	void calcInfo()
	{

	};
	void drawInfo()
	{
		
	};
	void loadCurve(char *filename)
	{
		crv.loadCurveFromFile(filename);
		for(int i=0;i<crv.getSize();i++)
		{
			Vector2 *v=new Vector2(crv.getPoint(i));
			vecList.insert(vecList.end(),v);
		}
	};
	void saveCurve(char *filename)
	{
		switch(EditMode)
		{
		case TRACTION:
			traction.AeroRollcrv.saveCurvetoFile("aeroroll.txt");
			for(int i=1;i<=5;i++)
			{
				char txt[128];
				sprintf(txt,"traction%d",i);
				traction.tractioncrv[i].saveCurvetoFile(txt);
			}
			break;
		case TORQUE:
		case CURVE:
			{
				crv.reset();
				if(EditMode==TORQUE)crv.setName("torquecrv");
				else if(EditMode==CURVE)crv.setName("crv");
				for(int i=0;i<vecList.size();i++)
					crv.addPoint(vecList[i]->x, vecList[i]->y);
				crv.saveCurvetoFile(filename);
			}
			break;
		case PACEJKA:
			{
				TiXmlDocument root;

				TiXmlElement emt("pacejka");

				char txt[256],bcde[256];
				TiXmlElement emt_1("fx");
				sprintf(bcde,"%f,%f,%f,%f",pacejka._B.x,pacejka._C.x,pacejka._D.x,pacejka._E.x);
				emt_1.SetAttribute("BCDE",bcde);
				sprintf(txt,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
					pacejka.b0 ,pacejka.b1 ,pacejka.b2 ,pacejka.b3 ,pacejka.b4 ,
					pacejka.b5 ,pacejka.b6 ,pacejka.b7 ,pacejka.b8 ,pacejka.b9 ,
					pacejka.b10,pacejka.b11,pacejka.b12);
				emt_1.SetAttribute("coef",txt);

				TiXmlElement emt_2("fy");
				sprintf(bcde,"%f,%f,%f,%f",pacejka._B.y,pacejka._C.y,pacejka._D.y,pacejka._E.y);
				emt_2.SetAttribute("BCDE",bcde);
				sprintf(txt,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
					pacejka.a0 ,pacejka.a1 ,pacejka.a2 ,pacejka.a3 ,pacejka.a4 ,
					pacejka.a5 ,pacejka.a6 ,pacejka.a7 ,pacejka.a8 ,pacejka.a9 ,
					pacejka.a10 ,pacejka.a111 ,pacejka.a112 ,pacejka.a12,pacejka.a13);
				emt_2.SetAttribute("coef",txt);

				TiXmlElement emt_3("fz");
				sprintf(bcde,"%f,%f,%f,%f",pacejka._B.z,pacejka._C.z,pacejka._D.z,pacejka._E.z);
				emt_3.SetAttribute("BCDE",bcde);
				sprintf(txt,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", 
					pacejka.c0 ,pacejka.c1 ,pacejka.c2 ,pacejka.c3 ,pacejka.c4 ,
					pacejka.c5 ,pacejka.c6 ,pacejka.c7 ,pacejka.c8 ,pacejka.c9 ,
					pacejka.c10,pacejka.c11,pacejka.c12,pacejka.c13,pacejka.c14,
					pacejka.c15,pacejka.c16,pacejka.c17);
				emt_3.SetAttribute("coef",txt);


				emt.InsertEndChild( *emt_1.ToElement());
				emt.InsertEndChild( *emt_2.ToElement());
				emt.InsertEndChild( *emt_3.ToElement());

				root.InsertEndChild(*emt.ToElement());
				root.SaveFile(filename);
			}
			break;
		}

	};
	void drawPacejka()
	{
		bool first=1;
		Vector2 o1,o2,o3;
		Vector2 fxcvt=Vector2(0.1f,200.0f);
		Vector2 fycvt=Vector2(1.0f,200.0f);//0.005);
		Vector2 fzcvt=Vector2(1.0f,400.0f/300.0f);
		float rad20cvt=0.34906585f/20.0f;
		for(float i=-20.0;i<20.0;i+=0.1f)
		{
			pacejka.SetSlipAngle(i*rad20cvt); //弧度为20的转换系数
			pacejka.SetSlipRatio(i*fxcvt.x);
			pacejka.Calculate();
			float fz=pacejka.GetFz()*1000;
			float x=pacejka.GetFx()/fz *fxcvt.y;
			float y=pacejka.GetFy()/fz *fycvt.y;
			float z=pacejka.GetMz()*fzcvt.y;

			Vector2 v1=VXV(Vector2(-i,x),AxisScale)+Orgin;
			Vector2 v2=VXV(Vector2(-i,y),AxisScale)+Orgin;
			Vector2 v3=VXV(Vector2(-i,z),AxisScale)+Orgin;
			
			if(first)
			{
				first=0;
				o1=v1;
				o2=v2;
				o3=v3;
			}
			else
			{
				SetClipRect(_min.x,_min.y,_max.x-_min.x, _max.y-_min.y);
				line(o1.x,o1.y, v1.x,v1.y,2);
				line(o2.x,o2.y, v2.x,v2.y,15);
				line(o3.x,o3.y, v3.x,v3.y,36);
				SetClipRect(0,0,WIDTH,HEIGHT);
				o1=v1;
				o2=v2;
				o3=v3;
			}
		}
		//draw info
		print_string(_min.x+20,_min.y+12, 2, "Fx/Fz Nm/Nm 2.0" );
		print_string(_min.x+20,_min.y+22, 15,"Fy/Fz Nm/Nm 2.0" );
		print_string(_min.x+20,_min.y+32, 36,"Mz    Nm    400" );

		print_string(_max.x-60,Orgin.y+20, 4, "2.00 SR");
		print_string(_max.x-60,Orgin.y+30, 17,"20.0 SA");
		print_string(_max.x-60,Orgin.y+40, 38,"20.0 SA");
		Vector2 mp=getMouse();
		if((mp.x>_min.x && mp.x<_max.x && mp.y>_min.y && mp.y<_max.y ))
		{
			Vector2 ms=VXV((getMouse()-Orgin),1.0f/AxisScale);ms.y=-ms.y;
			float x=ms.x*0.1f;
			float y=ms.y/200.0f;
			print_fnum(getMouse().x,getMouse().y-20,x,4);
			print_fnum(getMouse().x,getMouse().y-10,y,4);
		}
	};
	void clearEdit()
	{
		selpoint=-1;
		editing=false;
		if(torqueconsumption==0)//torque
		{
			crv.reset();
			for(int i=0;i<vecList.size();i++)
				crv.addPoint(vecList[i]->x,vecList[i]->y);
		}
		else if(torqueconsumption==1)//consumption
		{
			fuelcrv.reset();
			for(int i=0;i<vecList_fuel.size();i++)
				fuelcrv.addPoint(vecList_fuel[i]->x,vecList_fuel[i]->y);
		}
	}
	void editPoint(Vector2 pt)
	{
		if(!canEdit())return;
		Vector2 point=pt-Orgin;
		point.y=-point.y;
		if(torqueconsumption==0)
		{
			Vector2 v=VXV(point,1.0f/AxisScale);
			//v.y=-v.y;
			if(selpoint!=-1)
			{
				*vecList[selpoint]=v;
			}
		}
		else
		{
			Vector2 fuelcrvScale=AxisScale;
			Vector2 v=VXV(point,1.0f/fuelcrvScale);
			//v.y=-v.y;
			if(selpoint!=-1)
			{
				*vecList_fuel[selpoint]=v;
			}
		}
	};
	bool canEdit()
	{
		Vector2 mp=getMouse();
		return (mp.x>_min.x && mp.x<_max.x && mp.y>_min.y && mp.y<_max.y && canedit);
	};
	void drawTraction()
	{
		Vector2 ms=getMouse()-Orgin;
		ms=VXV(ms,1.0f/AxisScale);
		ms.y=-ms.y;
		print_fnum(_max.x-100, _min.y-8, ms.x,4);
		print_fnum(_max.x-100, _min.y+2, ms.y,4);

		if(!traction.isCreated())return;
		for(int gear=1;gear<=5;gear++)
		{
			float first=1;
			Vector2 ot;
			for(float ua=0;ua<=MaxAxisX;ua+=10)
			{
				float ft=traction.getValue(gear,ua);
				Vector2 vt=VXV(Vector2(ua,ft),AxisScale);
				vt.y=-vt.y;
				vt=vt+Orgin;
				if(first)
				{
					first=0;
					ot=vt;
				}
				else
				{
					SetClipRect(_min.x,_min.y,_max.x-_min.x, _max.y-_min.y);
					line(ot.x,ot.y, vt.x,vt.y, 3);
					ot=vt;
					SetClipRect(0,0,WIDTH,HEIGHT);
				}
			}
		}

		Vector2 ot;
		float first=1;
		for(float ua=0;ua<=MaxAxisX;ua+=10)
		{
			float f=traction.getARValue(ua);
			Vector2 vt=VXV(Vector2(ua,f),AxisScale);
			vt.y=-vt.y;
			vt=vt+Orgin;
			if(first)
			{
				first=0;
				ot=vt;
			}
			else
			{
				SetClipRect(_min.x,_min.y,_max.x-_min.x, _max.y-_min.y);
				line(ot.x,ot.y, vt.x,vt.y, 15);
				ot=vt;
				SetClipRect(0,0,WIDTH,HEIGHT);
			}
		}
		//draw info
		for(int i=1;i<=5;i++)
		{
			ot=traction.tractioncrv[i].getMax2();
			ot=VXV(ot,AxisScale);
			ot.y=-ot.y;
			ot=ot+Orgin;
			if(ot.x>_max.x)ot.x=_max.x-5;
			print_num(ot.x,ot.y-10, i,2);
		}

		print_string(_min.x-11,_min.y-8,4,"Ft(N)");
		print_string(_max.x-62,_max.y-14,4,"Ua(km/h)");
	};
	void drawCurve()
	{
		int first=1;
		for(int i=0;i<vecList.size();i++)
		{
			Vector2 v= VXV(*vecList[i],AxisScale)+Orgin;
			Circle(v.x,v.y,2,30);

			if(first)	first=0;
			else
			{
				Vector2 v0= *vecList[i-1]+Orgin;
				SetClipRect(_min.x,_min.y,_max.x-_min.x, _max.y-_min.y);
				line(v0.x,v0.y,v.x,v.y,1);
				SetClipRect(0,0,WIDTH,HEIGHT);
			}
		}

	};
	void drawAxis(Vector2 org, Vector2 axis, float scale,float range_min, float range_max, float unit,float axismax,bool sideflg=false)
	{
		axis.Unit();
		Vector2 ax1=axis^1;		ax1.Unit();

		Vector2 o1=axis*range_min*scale+org;
		Vector2 o2=axis*range_max*scale+org;

		Line_(o1.x,o1.y, o2.x,o2.y, 4);
		float dot=2;
		int idx=-1;
		for(float i=0;i<=axismax;i+=unit)
		{
			idx+=1;
			if(i<range_min || i>range_max)
				continue;
			Vector2 d=axis*i*scale+org;
			Vector2 d1=d+ax1*dot;
			Vector2 d2=d-ax1*dot;
			Line_(d1.x,d1.y, d2.x,d2.y, 4);

			Vector2 d3;
			if(sideflg)	{	 d3= d1+ax1*3;	}
			else		{	 d3= d2-ax1*3;	}
			print_num(d3.x,d3.y,idx,4);
		}
	}
	void drawTorqueCurve()//发动机工况
	{
		//draw power axis   (kw)
		drawAxis(Orgin+Vector2(480,0),Vector2(0,-1), powerscale, 50,400, 40, 400);
		print_string(Orgin.x+444,Orgin.y-492, 4, "kW (400)");
		print_string(Orgin.x+444,Orgin.y-482, 4, "Unit(40)");

		//draw fuel consumption axis
		drawAxis(Orgin+Vector2(450,0),Vector2(0,-1), 40, 3,8, 1, 10 ); 

		//draw info
		print_string(_min.x-3,_min.y-8, 4,"Nm");
		print_string(_max.x-24, _max.y-12,4,"RPM");

		Vector2 ms=VXV((getMouse()-Orgin),1/AxisScale);

		for(int i=0;i<vecList.size();i++)
		{
			Vector2 m=getMouse();
			Vector2 cc=VXV(*vecList[i],AxisScale);
			cc.y=-cc.y;
			cc=cc+Orgin;
			if(GetLength(m,cc)<=4 )
			{
				ms=*vecList[i];
				ms.y=-ms.y;
				break;
			}
		}
		print_fnum(_min.x+140,_min.y+0,ms.x,4 );
		print_fnum(_min.x+140,_min.y+10,-ms.y,4 );

		float p1=1.0f/powerscale;
		float m1=-(getMouse().y-Orgin.y)*p1;
		print_fnum(_max.x-100,_min.y+10,m1,4);

		if(crv.isEmpty())return;



		int first=1;
		Vector2 o;
		//draw torque crv;
		for(float i=crv.getPoint(0).x;i<crv.getPoint(crv.getSize()-1).x;i+=1)
		{
			if(first)
			{
				first=0;
				o=VXV(Vector2(i,crv.getValue(i)),AxisScale);
				o.y=-o.y;
				o=o+Orgin;
			}
			else
			{
				Vector2 v=VXV(Vector2(i,crv.getValue(i)),AxisScale);
				v.y=-v.y;
				v=v+Orgin;

				SetClipRect(_min.x,_min.y,_max.x-_min.x, _max.y-_min.y);
				line(o.x,o.y, v.x,v.y,2);
				SetClipRect(0,0,WIDTH,HEIGHT);
				o=v;
			}
		}
		first=1;
		//calc and draw power crv
		for(float i=crv.getPoint(0).x;i<crv.getPoint(crv.getSize()-1).x;i+=1)
		{
			float rpm=i;
			float tq=crv.getValue(i);
			float pwr=rpm*tq / 9545.0f;
			if(first)
			{
				first=0;
				o=VXV(Vector2(i,-pwr),Vector2(AxisScale.x,powerscale))+Orgin;
			}
			else
			{
				Vector2 v=VXV(Vector2(i,-pwr),Vector2(AxisScale.x,powerscale))+Orgin;
				SetClipRect(_min.x,_min.y,_max.x-_min.x, _max.y-_min.y);
				line(o.x,o.y, v.x,v.y,2);
				SetClipRect(0,0,WIDTH,HEIGHT);
				o=v;
			}
		}
		
	};
	void drawAxisFrame()//画坐标系
	{
		float dot=2;//AxisScale.x;//*MaxAxisX;
		int idx=0;
		calcCurvePannel();
		switch(AxisType)
		{
		case AXIS2:
			{
				Vector2 maxx=VXV(Vector2(MaxAxisX,0),AxisScale)+Orgin;
				Vector2 miny=VXV(Vector2(0,-MaxAxisY),AxisScale)+Orgin;
				//Vector2 _min=miny;
				//Vector2 _max=maxx;

				//draw background
				Line_(_min.x-15,_min.y-15, _max.x+15, _max.y+15, 4,true);

				//draw Y axis
				Line_(miny.x,miny.y, Orgin.x,Orgin.y,4);
				for(float y=0;y<MaxAxisY;y+=UnitY)
				{
					Vector2 yyt=VXV(Vector2(0, -y),AxisScale)+Orgin;
					Line_(yyt.x-dot,yyt.y, yyt.x+dot,yyt.y,4);
					print_num(yyt.x-12,yyt.y,idx++,6);
				}
				idx=0;
				//draw X axis
				Line_(Orgin.x,Orgin.y, maxx.x, maxx.y,4);
				for(float x=0;x<MaxAxisX;x+=UnitX)
				{
					Vector2 xxr=VXV(Vector2(x,0),AxisScale)+Orgin;
					Line_(xxr.x,xxr.y-dot, xxr.x,xxr.y+dot,4);
					print_num(xxr.x,xxr.y+6,idx++,6);
				}
				
				//y
				print_string(miny.x+20,miny.y,4,"MAX:");
				print_fnum(miny.x + 70,miny.y, MaxAxisY,4,"%.1f");
				print_string(miny.x+20,miny.y+10, 4,"UNIT:");
				print_fnum(miny.x + 70,miny.y+10,UnitY,4,"%.1f");

				//x
				print_string(maxx.x-100,maxx.y-40,4,"MAX:");
				print_fnum(maxx.x - 50,maxx.y-40, MaxAxisX,4,"%.1f");
				print_string(maxx.x-100,maxx.y-30, 4,"UNIT:");
				print_fnum(maxx.x - 50,maxx.y-30,UnitX,4,"%.1f");

			}
			break;
		case AXIS4:
			{
				Vector2 minx=VXV(Vector2(-MaxAxisX,0),AxisScale) + Orgin;
				Vector2 maxx=VXV(Vector2( MaxAxisX,0),AxisScale) + Orgin;
				Vector2 miny=VXV(Vector2(0,-MaxAxisY),AxisScale) + Orgin;
				Vector2 maxy=VXV(Vector2(0, MaxAxisY),AxisScale) + Orgin;
				//Vector2 _min=minx+miny-Orgin;
				//Vector2 _max=maxx+maxy-Orgin;
				//draw background
				Line_(_min.x-10,_min.y-10, _max.x+10,_max.y+10,4,true);
				//draw X axis
				Line_(minx.x, minx.y, maxx.x, maxx.y,4);
				for(float x=0;x<MaxAxisX;x+=UnitX)
				{
					Vector2 xxl = VXV(Vector2(-x,0),AxisScale) + Orgin;
					Vector2 xxr = VXV(Vector2( x,0),AxisScale) + Orgin;
					Line_(xxl.x,xxl.y-dot, xxl.x,xxl.y+dot,4);
					Line_(xxr.x,xxr.y-dot, xxr.x,xxr.y+dot,4);
					//print_num(xxl.x,xxl.y+8,-idx,6);
					print_num(xxr.x,xxr.y+8,idx,6);
					idx++;
				}
				idx=0;
				//draw Y axis
				Line_(miny.x, miny.y, maxy.x, maxy.y,4);
				for(float y=0;y<MaxAxisY;y+=UnitY)
				{
					Vector2 yyt = VXV(Vector2(0,-y),AxisScale) + Orgin;
					Vector2 yyb = VXV(Vector2(0, y),AxisScale) + Orgin;
					Line_(yyt.x-dot,yyt.y, yyt.x+dot,yyt.y,4);
					Line_(yyb.x-dot,yyb.y, yyb.x+dot,yyb.y,4);
					//print_num(yyt.x-25,yyt.y,-idx,6);
					print_num(yyb.x-16,yyb.y, idx,6);
					idx++;
				}

				//y
				print_string(miny.x+20,miny.y,4,"MAX:");
				print_fnum(miny.x + 70,miny.y, MaxAxisY,4,"%.1f");
				print_string(miny.x+20,miny.y+10, 4,"UNIT:");
				print_fnum(miny.x + 70,miny.y+10,UnitY,4,"%.1f");

				//x
				print_string(maxx.x-90,maxx.y-30,4,"MAX:");
				print_fnum(maxx.x - 40,maxx.y-30, MaxAxisX,4,"%.1f");
				print_string(maxx.x-90,maxx.y-20, 4,"UNIT:");
				print_fnum(maxx.x - 40,maxx.y-20,UnitX,4,"%.1f");

			}
			break;
		case NONE:
			{
				Line_(_min.x-10,_min.y-10, _max.x+10,_max.y+10,4,true);
			}
			break;
		}
	};

	void drawCarPrevView(Vector2 pos)
	{
		Vector2 ps=pos+Orgin;
		Vector2 mmin=Vector2(0,0)+ps;
		Vector2 mmax=Vector2(250,250)+ps;
		Line_(mmin.x,mmin.y,mmax.x,mmax.y,4,true);

		SetClipRect(mmin.x,mmin.y,mmax.x-mmin.x, mmax.y-mmin.y);
		RDev.SetViewPortEx(Point3(mmin.x,mmin.y,0),45,mmax.x-mmin.x,mmax.y-mmin.y,100, PRJ_PERS);
		//do 3d stuff

//		redraw();

/*
		if(lmclked)
		{
			RayT rt=RDev.GetMouseVec(mx,my);
			if(RayOBBOverlap(rt,car.bodobb))
			{
				DrawOBB(car.bodobb,40,true);
			}
			for(int i=0;i<4;i++)
			{
				RayT rt=RDev.GetMouseVec(mx,my);
				//rt.end*=-1;
				if(RayOBBOverlap(rt,car.wheelobb[i]))
				{
					DrawOBB(car.wheelobb[i],40,true);
				}
			}
		}
*/

		RDev.SetViewPortEx(Point3(0,0,0),90,WIDTH,HEIGHT,WIDTH,PRJ_PERS);
		SetClipRect(0,0,WIDTH,HEIGHT);


	}
	void drawCarPrevView1(Vector2 pos)	//body mass edit
	{
		Vector2 ps=pos+Orgin;
		Vector2 mmin=Vector2(0,0)+ps;
		Vector2 mmax=Vector2(250,250)+ps;
		Line_(mmin.x,mmin.y,mmax.x,mmax.y,4,true);

		SetClipRect(mmin.x,mmin.y,mmax.x-mmin.x, mmax.y-mmin.y);
		RDev.SetViewPortEx(Point3(mmin.x,mmin.y,0),45,mmax.x-mmin.x,mmax.y-mmin.y,100, PRJ_PERS);
		//do 3d stuff

	//	redraw();

/*
		if(lmclked)
		{
			RayT rt=RDev.GetMouseVec(mx,my);
			if(RayOBBOverlap(rt,car.bodobb))
			{
				DrawOBB(car.bodobb,40,true);
			}
			for(int i=0;i<4;i++)
			{
				RayT rt=RDev.GetMouseVec(mx,my);
				//rt.end*=-1;
				if(RayOBBOverlap(rt,car.wheelobb[i]))
				{
					DrawOBB(car.wheelobb[i],40,true);
				}
			}
		}
*/

		RDev.SetViewPortEx(Point3(0,0,0),90,WIDTH,HEIGHT,WIDTH,PRJ_PERS);
		SetClipRect(0,0,WIDTH,HEIGHT);


	}

	void drawWheelSusEdit()
	{
		drawCarPrevView(Vector2(0,-230));
		print_string(Orgin.x-250,Orgin.y-220,1,"Wheel Param:",1,1);
		print_string(Orgin.x-250,Orgin.y,1,"Suspension Param:",1,1);

	};
	void drawWeightDistEdit()
	{
		drawCarPrevView(Vector2(0,-230));
		print_string(Orgin.x-250,Orgin.y-220,1, "Vehicle Infomation:",1,1);

		print_string(Orgin.x-250,Orgin.y+40,1, "MassPart Distribution:",1,1);
	};
	void drawTransmissEdit()
	{
		print_string(Orgin.x-250,Orgin.y-220,1, "GearBox Param:",1,1);
		print_string(Orgin.x-250,Orgin.y-40,1, "Transmision Param:",1,1);
		print_string(Orgin.x+20,Orgin.y-220,1, "Brake And Steer:",1,1);
	};
	void drawAssistEdit()
	{
		print_string(Orgin.x-250,Orgin.y-220,1, "Input Param:",1,1);
		print_string(Orgin.x+10,Orgin.y-220,1, "Camera Param:",1,1);
	};
	void drawGearEdit()
	{

	};
	void render()
	{


		switch(EditMode)
		{
		case PACEJKA:
			drawControlPoint();
			drawAxisFrame();
			drawPacejka();
			break;
		case CURVE:
			drawControlPoint();
			drawAxisFrame();
			drawCurve();
			break;
		case TORQUE:
			drawControlPoint();
			drawAxisFrame();
			drawTorqueCurve();
			break;
		case TRACTION:
			drawControlPoint();
			drawTraction();
			drawAxisFrame();
			break;
		case GEARS:
			drawAxisFrame();
			drawGearEdit();
			break;
		case TRANSMISS:
			drawAxisFrame();
			drawTransmissEdit();
			break;
		case WEIGHTDIST:
			drawAxisFrame();
			drawWeightDistEdit();
			break;
		case WHEELSUS:
			drawAxisFrame();
			drawWheelSusEdit();
			break;
		case ASSIST:
			drawAxisFrame();
			drawAssistEdit();
			break;
		case MAPEDIT:
			drawAxisFrame();
			break;
		}


/*		if(!crv.isEmpty())
		{
			for(float x=-MaxAxisX;x<MaxAxisX;x++)
			{
				float y=crv.getValue(x);
				Vector2 v=Vector2(x,y)+Orgin;
				Circle(v.x,v.y,1,3);
			}
		};
*/
	};
public:
	Vector2 getMouse()
	{
		return Vector2(mx,my);
	};
	void setOrgin(Vector2 org){Orgin=org;Orgin1=org;};
	void setOffset(Vector2 ps){Orgin=ps+Orgin1;};
	void setAxisType(int type){AxisType=type;};
	void setAxisX(float maxX,float unit){MaxAxisX=maxX;UnitX=unit;};
	void setAxisY(float maxY,float unit){MaxAxisY=maxY;UnitY=unit;};
	void setAxisScale(float scalex,float scaley){AxisScale=Vector2(scalex,scaley);};
	void calcCurvePannel()
	{
		if(AxisType==AXIS2)
		{
			Vector2 maxx=VXV(Vector2(MaxAxisX, 0),AxisScale)+Orgin;
			Vector2 miny=VXV(Vector2(0,-MaxAxisY),AxisScale)+Orgin;
			_min=miny;
			_max=maxx;
		}
		else if(AxisType==AXIS4)
		{
			Vector2 minx=VXV(Vector2(-MaxAxisX,0),AxisScale) + Orgin;
			Vector2 maxx=VXV(Vector2( MaxAxisX,0),AxisScale) + Orgin;
			Vector2 miny=VXV(Vector2(0,-MaxAxisY),AxisScale) + Orgin;
			Vector2 maxy=VXV(Vector2(0, MaxAxisY),AxisScale) + Orgin;
			_min=minx+miny-Orgin;
			_max=maxx+maxy-Orgin;
		}
		else if(AxisType==NONE)
		{
			_min=Vector2(-260,-240)+Orgin;
			_max=Vector2(260,240)+Orgin;
		}
	}
	void setEditMode(int mode)
	{
		EditMode=mode;
		switch(mode)
		{
		case TORQUE:	
			{
				setAxisType(AXIS2);	
				setAxisX(8000,1000);
				setAxisY(600,60);
				setAxisScale(0.062f,0.8f);
				setOrgin(Vector2(-250,240));
				crv.setFitingType(LINEAR);
				canedit=true;
			}
			break;
		case TRACTION:
			{
				setAxisType(AXIS2);
				setAxisX(220,22);
				setAxisY(20*1000,2000);
				setAxisScale(2.00f,0.0212f);
				setOrgin(Vector2(-200,200));
				crv.setFitingType(LINEAR);
				traction.reset();
				traction.load();
				traction.reCreate(&crv);
				canedit=false;
			}
			break;
		case CURVE:
			{
				setAxisType(AXIS2);	
				setAxisX(8000,1000);
				setAxisY(600,60);
				setAxisScale(0.062f,0.8f);
				setOrgin(Vector2(-250,240));
				crv.setFitingType(LINEAR);
				canedit=true;
			}
			break;
		case PACEJKA:	
			{
				setAxisType(AXIS4);
				setAxisX(20,2);
				setAxisY(400,40);
				setAxisScale(13,0.6f);
				setOrgin(Vector2(0,0));
				pacejka.Load();
				canedit=false;
			}
			break;
		case WHEELSUS:
			{
				setAxisType(NONE);
				setOrgin(Vector2(0,0));
			}
			break;
		case GEARS:
			{
				setAxisType(NONE);
				setOrgin(Vector2(0,0));
			}
			break;
		case WEIGHTDIST:
			{
				setAxisType(NONE);
				setOrgin(Vector2(0,0));
			}
			break;
		case TRANSMISS:
			{
				setAxisType(NONE);
				setOrgin(Vector2(0,0));
			}
			break;
		case ASSIST:
			{
				setAxisType(NONE);
				setOrgin(Vector2(0,0));
			}
			break;
		case MAPEDIT:
			{
				setAxisType(NONE);
				setOrgin(Vector2(0,0));
			}
			break;
		}
		calcCurvePannel();
	};
	void drawControlPoint()
	{
		int first=1;
		//draw torque crv
		for(int i=0;i<vecList.size();i++)
		{
			Vector2 v= VXV(*vecList[i],AxisScale);
			v.y=-v.y;
			v=v+Orgin;
			Circle(v.x,v.y,3,5);

			if(first)	first=0;
			else
			{
				Vector2 v0= VXV(*vecList[i-1],AxisScale);
				v0.y=-v0.y;
				v0=v0+Orgin;
				line(v0.x,v0.y,v.x,v.y,6);
			}

		}
		//draw consumption
		first=1;
		Vector2 FuelCrvScale=AxisScale;
		for(int i=0;i<vecList_fuel.size();i++)
		{
			Vector2 v= VXV(*vecList_fuel[i],FuelCrvScale);
			v.y=-v.y;
			v=v+Orgin;
			Circle(v.x,v.y,3,5);
			if(first) first=0;
			else
			{
				Vector2 v0=VXV(*vecList_fuel[i-1],FuelCrvScale);
				v0.y=-v0.y;
				v0=v0+Orgin;
				line(v0.x,v0.y,v.x,v.y,6);
			}
		}
	};
	void clear()
	{
		if(torqueconsumption==0)
		{
			for(int i=0;i<vecList.size();i++)
				delete vecList[i];
			vecList.clear();
			crv.reset();
		}
		else
		{
			for(int i=0;i<vecList_fuel.size();i++)
				delete vecList_fuel[i];
			vecList_fuel.clear();
			fuelcrv.reset();
		}
	};
	void AddPoint(Vector2 pt,bool real=false)
	{
		if(real==true)
		{
			if(torqueconsumption==0)//torque
			{
				Vector2 *point=new Vector2(pt);
				vecList.insert(vecList.end(),point);

				crv.reset();
				for(int i=0;i<vecList.size();i++)
					crv.addPoint(vecList[i]->x,vecList[i]->y);
			}
			else if(torqueconsumption==1)//fuel
			{
				Vector2 *point=new Vector2(pt);
				vecList_fuel.insert(vecList_fuel.end(),point);

				fuelcrv.reset();
				for(int i=0;i<vecList_fuel.size();i++)
					fuelcrv.addPoint(vecList_fuel[i]->x,vecList_fuel[i]->y);
			}

			return;
		}

		if(!canEdit())return;
		if(editing || selpoint!=-1)return;

		Vector2 *point=new Vector2(pt-Orgin);
		point->y=-point->y;
		if(torqueconsumption==0)//torque
		{
			*point=VXV(*point, 1.0f/AxisScale);
			for(int i=0;i<vecList.size();i++)
			{
				Vector2 cc=VXV(*vecList[i],AxisScale);
				cc.y=-cc.y;
				cc=cc+Orgin;
				if( GetLength(pt,cc)<=4 )
				{
					if(!editing && selpoint==-1)
					{
						selpoint=i;
						editing=true;
					}
					return;
				}
			}
			if(vecList.size())
			{
				if(point->x<vecList[0]->x)
				{
					vecList.insert(vecList.begin(),point);
				}
				else if(point->x>vecList[vecList.size()-1]->x)
				{
					vecList.insert(vecList.end(),point);
				}
				else
				{
					for(int i=0;i<vecList.size();i++)
					{
						if(point->x<vecList[i]->x)
						{
							std::vector<Vector2 *>::iterator it=vecList.begin()+i;
							vecList.insert(it,point);
							break;
						}
					}
				}
			}
			else
			{
				vecList.insert(vecList.end(),point);
			}
		}
		else if(torqueconsumption==1)
		{
			Vector2 fuelcrvScale=AxisScale;
			*point=VXV(*point, 1.0f/fuelcrvScale);
			for(int i=0;i<vecList_fuel.size();i++)
			{
				Vector2 cc=VXV(*vecList_fuel[i],fuelcrvScale);
				cc.y=-cc.y;
				cc=cc+Orgin;
				if( GetLength(pt,cc)<=4 )
				{
					if(!editing && selpoint==-1)
					{
						selpoint=i;
						editing=true;
					}
					return;
				}
			}
			if(vecList_fuel.size())
			{
				if(point->x<vecList_fuel[0]->x)
				{
					vecList_fuel.insert(vecList_fuel.begin(),point);
				}
				else if(point->x>vecList_fuel[vecList_fuel.size()-1]->x)
				{
					vecList_fuel.insert(vecList_fuel.end(),point);
				}
				else
				{
					for(int i=0;i<vecList_fuel.size();i++)
					{
						if(point->x<vecList_fuel[i]->x)
						{
							std::vector<Vector2 *>::iterator it=vecList_fuel.begin()+i;
							vecList_fuel.insert(it,point);
							break;
						}
					}
				}
			}
			else
			{
				vecList_fuel.insert(vecList_fuel.end(),point);
			}
		}
	}
	void setTorqueOrConsumption(int tq=1){torqueconsumption=tq;}
public:
	typedef struct PaceJkaPara
	{
		PaceJkaPara()
		{
			value=NULL;
			min=max=0;
		};
		void Init(std::string n,float _min,float _max,float *v, std::string dec,std::string _unt="")
		{
			name=n;
			desc=dec;
			unit=_unt;
			min=_min;
			max=_max;
			value=v;
		};
		void SetSource(float *v)
		{
			value=v;
		};
		std::string name;
		std::string desc;
		std::string unit;//单位
		float min,max;
		float* value;
	}DataPara;
public:
	Vector2 Orgin,Orgin1;
	int AxisType;
	float MaxAxisX,MaxAxisY;
	float UnitX,UnitY;
	float powerscale;
	Vector2 AxisScale;
	int EditMode;
	int torqueconsumption;
	bool editing;
	bool canedit;
	int selpoint;

	Vector2 _min,_max;
	std::vector<Vector2 *> vecList;
	std::vector<Vector2 *> vecList_fuel;
	Curve crv,fuelcrv;
	Pacejka pacejka;
	Traction traction;
	PaceJkaPara a[20],b[20],c[20];
	DataPara ig0,ig[10],A,transmissionef,wheelrad,rollcoef,weight,Cd;


	//wheel_sus
	DataPara wheelposfl[3],wheelposfr[3],wheelposrl[3],wheelposrr[3],wheelsizef[3],wheelsizer[3],wheeltyref[3],wheeltyrer[3];

	DataPara susaxisf[3],susaxisr[3],susspringdampf[2],susspringdampr[2],susarbf[2],susarbr[2],sustoecamber[2];
	//tramsmition
	DataPara gearchangupdown[2],tramtractiondiff[2],tramclutch[3];
	DataPara bsbrake[3],bssteer[1];
	//assist
	DataPara steeringwheel[3],throttle[3],brake[3],clutch[3];
	DataPara camera0[6],camera1[6],camera2[6],camera3[6],camera4[6];
	//weightdist
	DataPara masspartmain[7],masspartchassis[7],masspartmiddle[7],
		masspartfront[7],masspartrear[7],masspartengin[7];

	CarDefinitionT	carDef;
};



int MyColidfunc( Contact *contacts, Body* bodyA, Body* bodyB)
{
	int cts=0;
	if(bodyA->shapetype==S_OBB && bodyB->shapetype==S_OBB)
		cts=_BoxBoxColid(contacts,bodyA,bodyB);
	else if(bodyA->shapetype==S_OBB && bodyB->shapetype==S_OBB)
		cts=_BoxBoxColid(contacts,bodyB,bodyA);

	else if(bodyA->shapetype==S_SPHERE && bodyB->shapetype==S_SPHERE)
		cts=_SphereSphereColid(contacts,bodyA,bodyB);
	else if(bodyA->shapetype==S_SPHERE && bodyB->shapetype==S_SPHERE)
		cts=_SphereSphereColid(contacts,bodyB,bodyA);

	else if(bodyA->shapetype==S_SPHERE && bodyB->shapetype==S_OBB)
		cts=_SphereBoxColid(contacts,bodyA,bodyB);
	else if(bodyA->shapetype==S_OBB && bodyB->shapetype==S_SPHERE)
		cts=_SphereBoxColid(contacts,bodyB,bodyA);

	return cts;
}





/*
void GroundSphereCollid(RigidBody *rbd)
{
	float grd=0;
	if(rbd->pos.y+10>grd)
	{
		float dep=grd-(rbd->pos.y+10);
		//rbd->lvel.y= dep;
		rbd->force.y=1.0f/0.01*dep;
	}
}
*/



BLBBox bbox;


void DrawBLBox(BLBBox &box,int c)
{
	Vector3 x=box.GetCenter();
	Vector3 ax[3];
	ax[0]=box.GetSide(box.shortestAxisIndex_);
	ax[1]=box.GetSide(box.longestAxisIndex_);
	ax[2]=box.GetSide(box.midAxisIndex_);
	ax[0].Unit();
	ax[1].Unit();
	ax[2].Unit();
	ax[0]=ax[0]*box.GetSideLength(box.shortestAxisIndex_);
	ax[2]=ax[2]*box.GetSideLength(box.midAxisIndex_);
	float r=box.GetMidBoxSideLength()*0.5f;
	float h=box.GetCylinderAxisHeight();


#define BLB_SEG 12.0f
	int j=0;
	float sx,sy,sz,i;
	Vector3 ofs=ax[1]*(h*0.5f);
	Vector3 p,p1;
	Vector3 vt[12+1],vt1,v;
	for(i=0;i<=360;i+=360.0f/BLB_SEG)
	{
		sx=r*cos(i*Pi);
		sz=r*sin(i*Pi);
		p=x+ax[0]*sx+ax[2]*sz;
		vt[j++]=p;
	}
	for(sy=0;sy<=h;sy+=h/8.0f)
	{
		j=0;
		for(i=0;i<=360;i+=360.0f/BLB_SEG)
		{
			sx=r*cos(i*Pi);
			sz=r*sin(i*Pi);
			p=x+ax[0]*sx+ax[1]*sy+ax[2]*sz;

			//Vector3 rr=ax[0]*sx+ax[2]*sz;
			//Vector3 rr1=box.GetRadius(rr);
			if(j>0)
			{
				v=(vt1-vt[j-1])|(vt[j]-vt[j-1]);
				v.Unit();
				if(v*RDev.SysCamera->ViewDir<0)
				{
					//box.GetRadius(
					line3(vt[j-1]-ofs,vt[j]-ofs,c);
					line3(vt1-ofs,p-ofs,c);
					line3(vt1-ofs,vt[j-1]-ofs,c);
					line3(p-ofs,vt[j]-ofs,c);
				}
				vt[j-1]=vt1;
			}
			vt1=p;	j++;
			//pset3(p,c);
		}
		vt[j-1]=vt1;
	}
	
	sy=-90+180.0f/BLB_SEG;
	j=0;
	for(i=0 ;i<=360;i+=360.0f/BLB_SEG)
	{
		p.x=cos(i*Pi)*r*cos(sy*Pi);
		p.z=sin(i*Pi)*r*cos(sy*Pi);
		p.y=sin(sy*Pi)*r;
		p1=ax[0]*p.x+ax[1]*p.y+ax[2]*p.z;
		vt[j++]=p1;
	}
	vt1=vt[0];
	float w;Vector3 v1;
	Vector3 vh=ax[1]*h;
	for(w=sy+180/BLB_SEG;w<=0;w+=180.0f/BLB_SEG)
	{
		j=0;
		for(i=0 ;i<=360;i+=360.0f/BLB_SEG)
		{
			p.x=cos(i*Pi)*r*cos(w*Pi);
			p.z=sin(i*Pi)*r*cos(w*Pi);
			p.y=sin(w*Pi)*r;
			p1=ax[0]*p.x+ax[1]*p.y+ax[2]*p.z;
			if(j>0)
			{
				v=(vt1-vt[j-1])|(vt[j]-vt[j-1]);
				v1=(vt1-vt[j])|(p1-vt[j]);
				if(v*RDev.SysCamera->ViewDir>0||v1*RDev.SysCamera->ViewDir>0)
				{
					line3(vh+VXV(vt[j-1],-1,-1,-1)+x-ofs,vh+VXV(vt[j],-1,-1,-1)+x-ofs,c);
					line3(vh+VXV(vt1,-1,-1,-1)+x-ofs,vh+VXV(p1,-1,-1,-1)+x-ofs,c);
					line3(vh+VXV(vt1,-1,-1,-1)+x-ofs,vh+VXV(vt[j-1],-1,-1,-1)+x-ofs,c);
					line3(vh+VXV(p1,-1,-1,-1)+x-ofs,vh+VXV(vt[j],-1,-1,-1)+x-ofs,c);
				}
				else
				{
					line3(vt[j-1]+x-ofs,vt[j]+x-ofs,c);
					line3(vt1+x-ofs,p1+x-ofs,c);
					line3(vt1+x-ofs,vt[j-1]+x-ofs,c);
					line3(p1+x-ofs,vt[j]+x-ofs,c);
				}
				vt[j-1]=vt1;
			}			
			vt1=p1;
			j++;
		}
		vt[j-1]=vt1;
	}
#undef BLB_SEG
}


#define DRAWAABB
void DrawGeometry(Geometry *geom,int clr)
{
	Vector3 pos=geom->getRealPos();
	Vector3 axs[3];
	geom->getRealAxis(axs);

	
	if(geom->GeometryType==SPHERE)
	{
		DrawSphere1(pos,axs,geom->radius,clr);
	}
	else if(geom->GeometryType==CAPSULE)
	{
		DrawCapsul(pos,axs,geom->radius,geom->radius0,clr);
	}
	else if(geom->GeometryType==BOX)
	{
		DrawOBB(pos,axs,geom->size*0.5,clr);
	}

}
void DrawRigidBody(RigidBody *body)
{ 
	for(Geometry *geom=(Geometry*)body;geom!=NULL;geom=geom->next)
	{
		DrawGeometry(geom,1);
	}
//	DrawAABB(body->getAABB(),30);
//	Matrix3 mt=body->getRealRot();
//	Vector3 v[3];
//	v[0]=ROW(mt,0);
//	v[1]=ROW(mt,1);
//	v[2]=ROW(mt,2);
//	DrawVec3(body->linPos,v[0],1);
//	DrawVec3(body->linPos,v[1],1);
//	DrawVec3(body->linPos,v[2],1);
}

RigidBody m_newbody[120];
RigidBody m_groundbox;
const int numbody=3;
class VehicleSimu
{
public:
	VehicleSimu(){};
	void init(RenderDevice *r)
	{
		
		rd=r;
		obj.clr=4;
		obj.BoundCamDir(&(rd->GetCamera()->ViewDir));
		PGEN.BoundtoObj(&obj);
		PGEN.SetSegment(25,25,0);
		PGEN.SetRot(Vector3(1,0,0),PIDev2);
//		PGEN.GenQuadPlanS(50,50,0);
		PGEN.GenQuadPlanS(400,400,0);
		

		PGEN.SetPos(Vector3(-70,2,30));
		PGEN.GenBoxS(4,4,4);
		PGEN.SetPos(Vector3(-50,2,30));
		PGEN.GenBoxS(4,4,4);
		PGEN.SetPos(Vector3(-30,2,30));
		PGEN.GenBoxS(4,4,4);
		PGEN.SetPos(Vector3(-10,2,30));
		PGEN.GenBoxS(4,4,4);
		PGEN.SetPos(Vector3(10,2,30));
		PGEN.GenBoxS(4,4,4);
		PGEN.SetPos(Vector3(30,2,30));
		PGEN.GenBoxS(4,4,4);
		PGEN.SetPos(Vector3(50,2,30));
		PGEN.GenBoxS(4,4,4);
		PGEN.SetPos(Vector3(70,2,30));
		PGEN.GenBoxS(4,4,4);


		PGEN.SetPos(Vector3(100,10,-100));
		PGEN.SetRot(Vector3(1,0,0),PI);
		PGEN.SetSegment(20,20,0);
		PGEN.GenQuadPlanS(60,60,0);

		PGEN.SetRot(Vector3(1,0,0),PI);
		PGEN.SetPos(Vector3(-100,20,100));
		PGEN.SetSegment(2,2,2);
		PGEN.GenBoxS(4,40,40);
		obj.pos=Vector3(0,0,0);
		

/*		obj.clr=4;
		obj.BoundCamDir(&(rd->pCmpointer->ViewDir));
		PGEN.BoundtoObj(&obj);
		PGEN.SetSegment(25,25,0);
		PGEN.SetRot(Vector3(1,0,0),-3.14159265f/2.0f);
//		PGEN.GenSphereS(100);
		PGEN.GenQuadPlanS(1000,1000,0);

		//init vehicle
		loadGraphicModel("CarModelList.xml");
		loadPhysicsModel("CarPhysicList.xml");

		_vehicle.load("carPara.xml");
		_vehicle.create();
		_vehicle.setPosition(Vector3(0,-8,0));

		world=World(Vector3(0,0,0),2);
		world.SetColidFunc(MyColidfunc);
		for(int i=0;i<20;i++)
		{
			body[i].SetOBB(Vector3(84,24,84),10);
			Vector3 pos=Vector3(0,-24*i-20,0);
			body[i].SetPos(pos);
			//body[i]._vel=pos*0.01f;
			body[i]._angvel=Vector3(0,0,0);//Vector3(RND(500)-RND(500),RND(500)-RND(500),RND(500)-RND(500))*0.001f;
			//body[i].SetRot(Quat(Vector3(1,0,0),1));
			body[i].e=0.10f;
			world.Add(&body[i]);
		}

		ground.SetPos(Vector3(0,0,0));
		ground.SetRot(Quat(Vector3(1,0,0),3.14159265f));
		ground.SetOBB(Vector3(5000,10,5000),FLT_MAX);
		world.Add(&ground);

		
*/
		

		initialise();

		RESurfaceH *surface=obj.convert2Surface();
//		installCollisionMesh(&(getWorld()->surfacelist));
		installCollisionMesh(surface);
		installCollision(50);

		car.init(Vector3(0,3,0),Quat(Vector3(0,1,0),0));
//		RDev.GetCamera()->init(90,WIDTH,HEIGHT,WIDTH);
//		RDev.GetCamera()->LookAt(Point3(0,0,-80),Vector3(0,0,1),Vector3(0,-1,0));

/*


*/
		ORECT ort=ORECT(Vector3(0,0,0),Vector3(4,2,1));
		Vector3 verts[8];
		ort.GenVertics(verts);
		bbox.BuildBBox(verts);
		bbox.Init(Quat(),Vector3(0,0,0));


		for(int i=0;i<numbody;i++)
		{
			Geometry geom;
			if(i==0)
				geom.setSphere(3,10);
			else if(i==1)
				geom.setBox(5,5,5, 10);
			else if(i==2)
				geom.setCapsule(3,10,10);

			m_newbody[i].addGeometry(&geom);
			m_iWorld.RegisterPhyObj( &m_newbody[i]);
			m_newbody[i].initialise(Vector3(_rnd(100),5.0f,_rnd(100)),Vector3(0,0,0),Quat(),Vector3(0,0,0),0,0);
		}
/*		Geometry geom;
		geom.setCapsule(10,50,10);
		m_newbody[1].addGeometry(&geom);
		m_newbody[1].initialise(Vector3(100,260,0),Vector3(0,0,0),Quat(Vector3(1,0,0),40*Pi),Vector3(0,0,0),0,0);
		m_iWorld.RegisterPhyObj( &m_newbody[1]);
*/
	};
	void render()
	{		
//		DrawCoord(Vector3(0,0,0),Vector3(1,0,0),Vector3(0,1,0),Vector3(0,0,1));
		DrawObj(&obj);


		for(int i=0;i<numbody;i++)
		{
			DrawRigidBody(&m_newbody[i]);
		}
//		DrawRigidBody(&m_newbody[0]);

		//DrawRigidBody(&car.multibody.mainBody);

		if(getkey('Z'))
			m_newbody[0].linPos+=Vector3(0,1,0);
		if(getkey('X'))
			m_newbody[0].linPos+=Vector3(0,-1,0);
		if(getkey('R'))
			m_newbody[0].qRotPos=m_newbody[0].qRotPos*Quat(Vector3(1,0,0),1.0f*Pi);
		if(getkey('E'))
			m_newbody[0].qRotPos=m_newbody[0].qRotPos*Quat(Vector3(1,0,0),-1.0f*Pi);
		if(getkey(VK_SHIFT))
			m_newbody[0].qRotPos=m_newbody[0].qRotPos*Quat(Vector3(0,0,1),1.0f*Pi);
		if(getkey(VK_CONTROL))
			m_newbody[0].qRotPos=m_newbody[0].qRotPos*Quat(Vector3(0,0,1),-1.0f*Pi);

		if(getkey('L'))
//			m_newbody[0].linPos+=Vector3(1,0,0);
			m_newbody[0].addWorldWorldForce(RDev.GetCamera()->_u*830,m_newbody[0].linPos);
		if(getkey('J'))
//			m_newbody[0].linPos+=Vector3(-1,0,0);
			m_newbody[0].addWorldWorldForce(RDev.GetCamera()->_u*-830,m_newbody[0].linPos);
		if(getkey('I'))
//			m_newbody[0].linPos+=Vector3(0,0,1);
			m_newbody[0].addWorldWorldForce(RDev.GetCamera()->_n*830,m_newbody[0].linPos);
		if(getkey('K'))
//			m_newbody[0].linPos+=Vector3(0,0,-1);
			m_newbody[0].addWorldWorldForce(RDev.GetCamera()->_n*-830,m_newbody[0].linPos);

		if(getkey('G',true))
		{
			for(int i=0;i<numbody;i++)	
				m_newbody[i].initialise(Vector3(0,i*6.0f+2.0f,0),Vector3(0,0,0),Quat(),Vector3(0,0,0),0,0);
			if(RigidBody::g!=0)
			{
				RigidBody::g=0;
				m_newbody[0].linVel=Vector3(0,0,0);
				m_newbody[0].rotVel=Vector3(0,0,0);
			}
			else if(RigidBody::g==0)
				RigidBody::g=-9.8f;
		}
		static bool camflg=true;
		if(getkey('N',true))
		{
			camflg=!camflg;
			if(camflg)
			{
				initFreeCam(&car.multibody.mainBody);
			}
			else
			{
				initFreeCam(&m_newbody[0]);
			}
		}

		Vector3 v[3];
//		CreateAxis(v);
//		DrawBLBox(bbox,1);//Vector3(0,0,0),v,5,10,1);
//		DrawOBB(bbox,1);

/*
		DrawOBB(bbox,1,true);
		
		float step=0.001f;
		static float xa=0,za=0;
		if(getkey('I'))xa+=step;
		else if(getkey('K'))xa-=step;
		if(getkey('J'))za+=step;
		else if(getkey('L'))za-=step;

		static float xs=0,ys=4,zs=0;
		if(getkey(VK_LEFT))xs+=step;
		else if(getkey(VK_RIGHT))xs-=step;
		if(getkey(VK_PRIOR))ys+=step;
		else if(getkey(VK_NEXT))ys-=step;
		if(getkey(VK_UP))zs+=step;
		else if(getkey(VK_DOWN))zs-=step;
		

		Quat qtx(Vector3(1,0,0),xa);
		Quat qtz(Vector3(0,0,1),za);
		Quat qt=qtx*qtz;
		Vector3 ps(xs,ys,zs); 
		
		bbox.Updata(qt,ps);
*/
/*
		Vector3 bodypos=ps;Quat bodyrot=qt;BLBBox box=bbox;
		Vector3 lastuncoldi=bodypos;
		bool hitworldboarder=false;
		bool touchground=false;
		bool cold=false;
		Vector3 colpoint;
		Vector3 sumbk=DetectAndHandleWorldCollisions(&m_iWorld,bodypos,colpoint,lastuncoldi,box,hitworldboarder,touchground,cold);
		if(cold)
		{
			//printf("COLLIDING!!!!!!!!!!!!!!!!!!!!!\n");
			Vector3 vel=bodypos-ps;
			DrawSphere(colpoint,0.05,30);
			DrawVec3(colpoint,vel,1);
			line3(colpoint,colpoint+sumbk,30);
		}
*/



//		float alp=(GetTickCount()/10)%200;
//		float alp1=(GetTickCount()/10)%50;
//		



		static int pp=0;
		int nn=0;
		float sizes=m_iWorld.nodeInfoT_.numXNodes
			*m_iWorld.nodeInfoT_.numYNodes
			*m_iWorld.nodeInfoT_.numZNodes;
		for( size_t y = 0; y < m_iWorld.nodeInfoT_.numYNodes; y++ )
			for( size_t z = 0; z < m_iWorld.nodeInfoT_.numZNodes; z++ )
				for( size_t x = 0; x < m_iWorld.nodeInfoT_.numXNodes; x++ )
				{
					// get the node
					SWNodeConstructT *pNode = m_iWorld.pConstruct_->GetNode( x,y,z );

					//DrawAABB(pNode->aabb,30,true);
					if(getkey('H',true))
					{
						pp++;
						if(pp>=sizes)pp=0;
					}

					if(pp==nn)
						DrawAABB(pNode->collDetRoot,30,true);

					nn++;
					if(nn>=sizes)nn=0;
				}

		float stp=10;
//		_int64 fl=_fps/100000000;
//		fl=fl/stp;
//
		static bool phyenable=true;
		if(getkey('C',true))phyenable=!phyenable;
		if(phyenable)
		{
			evolveKey(0.001f);

			m_iWorld.Step(0.01f);

			for (int i = 0; i < stp;i++)
					carEvolve(0.001f);
		
			handelCollision();
			moveFreeCam(0.1f);
		}
//		drawWorld();
		redraw();

		static bool ds=0;
		if(getkey('Y',true))ds=!ds;
		if(ds)
			DrawOBB(car.m_bodybox,1,true);

/*
		if(lmclked)
		{
			RayT rt=RDev.GetMouseVec(mx,my);
			if(RayOBBOverlap(rt,car.bodobb))
			{
				DrawOBB(car.bodobb,40,true);
			}
			for(int i=0;i<4;i++)
			{
				RayT rt=RDev.GetMouseVec(mx,my);
				//rt.end*=-1;
				if(RayOBBOverlap(rt,car.wheelobb[i]))
				{
					DrawOBB(car.wheelobb[i],40,true);
				}
			}
		}
*/

/*		if(getkey(VK_SPACE,true))
			world._gravity=Vector3(0.0f,9.8f,0.0f);
		if(getkey('I'))
			body[1]._AddForce(Vector3(5000,0,0),body[1]._bpos);
		else if(getkey('K'))
			body[1]._AddForce(Vector3(-5000,0,0),body[1]._bpos);
		else if(getkey('J'))
			body[1]._AddForce(Vector3(0,0,5000),body[1]._bpos);
		else if(getkey('L'))
			body[1]._AddForce(Vector3(0,0,-5000),body[1]._bpos);
*/

//		_vehicle.updata(0.01);
//		_vehicle.paint();

	};
public:
	RenderDevice *rd;
	Object3d obj;
	World world;
	Body body[20];
	Body ground;

};


class CarSim
{
public:
	void gameinit();	
	void render();
	void setmode(int mode)
	{
		switch(mode)
		{
		case PACEJKA:
			{
			}
			break;
		case TRACTION:
			{
			}
			break;
		case TORQUE:
			{
			}
			break;
		case CURVE:
			{
			}
			break;
		}
	};
	void setEditPara(int mode,bool visbale)
	{
		switch(mode)
		{
		case PACEJKA:
			{
				EditDlg.GetSlider(8)->SetVisible(visbale);
				EditDlg.GetSlider(9)->SetVisible(visbale);
				EditDlg.GetSlider(10)->SetVisible(visbale);
				EditDlg.GetSlider(11)->SetVisible(visbale);
				EditDlg.GetSlider(12)->SetVisible(visbale);


				EditDlg.GetComboBox(7)->SetVisible(visbale);
				EditDlg.GetComboBox(16)->SetVisible(visbale);
				EditDlg.GetComboBox(17)->SetVisible(visbale);
				EditDlg.GetComboBox(17)->SetLocation(10,230+170);

				EditDlg.GetStatic(19)->SetVisible(visbale);
				EditDlg.GetStatic(20)->SetVisible(visbale);
				EditDlg.GetStatic(21)->SetVisible(visbale);
				EditDlg.GetStatic(22)->SetVisible(visbale);
				EditDlg.GetStatic(23)->SetVisible(visbale);

				EditDlg.GetEditBox(24)->SetVisible(visbale);
			}
			break;
		case TRACTION:
			{
				EditDlg.GetSlider(17)->SetVisible(visbale);
				EditDlg.GetComboBox(18)->SetVisible(visbale);
				EditDlg.GetStatic(24)->SetVisible(visbale);
			}
			break;
		case TORQUE:
			{
				EditDlg.GetCheckBox(15)->SetVisible(visbale);
				EditDlg.GetRadioButton(26)->SetVisible(visbale);
				EditDlg.GetRadioButton(27)->SetVisible(visbale);
			}
			break;
		case CURVE:
			{
				EditDlg.GetCheckBox(15)->SetVisible(visbale);
			}
			break;
		case WHEELSUS:
			{
				EditDlg.GetComboBox(17)->SetLocation(10,240);
				EditDlg.GetComboBox(17)->SetVisible(visbale);
				EditDlg.GetComboBox(20)->SetVisible(visbale);
				EditDlg.GetComboBox(21)->SetVisible(visbale);

				EditDlg.GetStatic(40)->SetVisible(visbale);
				EditDlg.GetStatic(41)->SetVisible(visbale);
				EditDlg.GetStatic(42)->SetVisible(visbale);
				EditDlg.GetStatic(43)->SetVisible(visbale);
				EditDlg.GetStatic(44)->SetVisible(visbale);
				EditDlg.GetStatic(45)->SetVisible(visbale);

				EditDlg.GetSlider(30)->SetVisible(visbale);
				EditDlg.GetSlider(31)->SetVisible(visbale);
				EditDlg.GetSlider(32)->SetVisible(visbale);
				EditDlg.GetSlider(33)->SetVisible(visbale);
				EditDlg.GetSlider(34)->SetVisible(visbale);
				EditDlg.GetSlider(35)->SetVisible(visbale);
			}
			break;
		case TRANSMISS:
			{
				EditDlg.GetComboBox(17)->SetLocation(10,240);
				EditDlg.GetComboBox(17)->SetVisible(visbale);
				EditDlg.GetComboBox(22)->SetVisible(visbale);
				EditDlg.GetComboBox(23)->SetVisible(visbale);
				EditDlg.GetComboBox(24)->SetVisible(visbale);
				EditDlg.GetComboBox(25)->SetVisible(visbale);

				EditDlg.GetStatic(46)->SetVisible(visbale);
				EditDlg.GetStatic(47)->SetVisible(visbale);
				EditDlg.GetStatic(48)->SetVisible(visbale);
				EditDlg.GetStatic(49)->SetVisible(visbale);
				EditDlg.GetStatic(50)->SetVisible(visbale);
				EditDlg.GetStatic(51)->SetVisible(visbale);
				EditDlg.GetStatic(52)->SetVisible(visbale);
				EditDlg.GetStatic(53)->SetVisible(visbale);
				EditDlg.GetStatic(54)->SetVisible(visbale);
				EditDlg.GetStatic(55)->SetVisible(visbale);

				EditDlg.GetSlider(36)->SetVisible(visbale);
				EditDlg.GetSlider(37)->SetVisible(visbale);
				EditDlg.GetSlider(38)->SetVisible(visbale);
				EditDlg.GetSlider(39)->SetVisible(visbale);
				EditDlg.GetSlider(40)->SetVisible(visbale);
				EditDlg.GetSlider(41)->SetVisible(visbale);
				EditDlg.GetSlider(42)->SetVisible(visbale);
				EditDlg.GetSlider(43)->SetVisible(visbale);
				EditDlg.GetSlider(44)->SetVisible(visbale);
				EditDlg.GetSlider(45)->SetVisible(visbale);

			}
			break;
		case WEIGHTDIST:
			{
				EditDlg.GetStatic(200)->SetVisible(visbale);
				EditDlg.GetStatic(201)->SetVisible(visbale);
				EditDlg.GetStatic(202)->SetVisible(visbale);
				EditDlg.GetStatic(203)->SetVisible(visbale);
				EditDlg.GetStatic(204)->SetVisible(visbale);
				EditDlg.GetStatic(205)->SetVisible(visbale);
				EditDlg.GetStatic(206)->SetVisible(visbale);
				EditDlg.GetStatic(207)->SetVisible(visbale);
				EditDlg.GetStatic(208)->SetVisible(visbale);
				EditDlg.GetStatic(209)->SetVisible(visbale);

				EditDlg.GetComboBox(29)->SetVisible(visbale);
				EditDlg.GetStatic(69)->SetVisible(visbale);
				EditDlg.GetStatic(70)->SetVisible(visbale);
				EditDlg.GetStatic(71)->SetVisible(visbale);

				EditDlg.GetSlider(55)->SetVisible(visbale);
				EditDlg.GetSlider(56)->SetVisible(visbale);
				EditDlg.GetSlider(57)->SetVisible(visbale);

				EditDlg.GetStatic(72)->SetVisible(visbale);
				EditDlg.GetStatic(73)->SetVisible(visbale);
				EditDlg.GetStatic(74)->SetVisible(visbale);

				EditDlg.GetSlider(58)->SetVisible(visbale);
				EditDlg.GetSlider(59)->SetVisible(visbale);
				EditDlg.GetSlider(60)->SetVisible(visbale);

				EditDlg.GetStatic(75)->SetVisible(visbale);
				EditDlg.GetSlider(61)->SetVisible(visbale);
			}
			break;
		case ASSIST:
			{
				EditDlg.GetComboBox(26)->SetVisible(visbale);
				EditDlg.GetComboBox(27)->SetVisible(visbale);
				EditDlg.GetComboBox(28)->SetVisible(visbale);

				EditDlg.GetStatic(56)->SetVisible(visbale);
				EditDlg.GetStatic(57)->SetVisible(visbale);
				EditDlg.GetStatic(58)->SetVisible(visbale);
				EditDlg.GetStatic(59)->SetVisible(visbale);
				EditDlg.GetStatic(60)->SetVisible(visbale);
				EditDlg.GetStatic(61)->SetVisible(visbale);
				EditDlg.GetStatic(62)->SetVisible(visbale);
				EditDlg.GetStatic(63)->SetVisible(visbale);
				EditDlg.GetStatic(64)->SetVisible(visbale);
				EditDlg.GetStatic(162)->SetVisible(visbale);
				EditDlg.GetStatic(163)->SetVisible(visbale);
				EditDlg.GetStatic(164)->SetVisible(visbale);

				EditDlg.GetSlider(46)->SetVisible(visbale);
				EditDlg.GetSlider(47)->SetVisible(visbale);
				EditDlg.GetSlider(48)->SetVisible(visbale);
				EditDlg.GetSlider(49)->SetVisible(visbale);
				EditDlg.GetSlider(50)->SetVisible(visbale);
				EditDlg.GetSlider(51)->SetVisible(visbale);
				EditDlg.GetSlider(52)->SetVisible(visbale);
				EditDlg.GetSlider(53)->SetVisible(visbale);
				EditDlg.GetSlider(54)->SetVisible(visbale);
				EditDlg.GetSlider(152)->SetVisible(visbale);
				EditDlg.GetSlider(153)->SetVisible(visbale);
				EditDlg.GetSlider(154)->SetVisible(visbale);

				EditDlg.GetCheckBox(20)->SetVisible(visbale);
				EditDlg.GetCheckBox(21)->SetVisible(visbale);
				EditDlg.GetCheckBox(22)->SetVisible(visbale);
				EditDlg.GetCheckBox(23)->SetVisible(visbale);
		
			}
			break;
		case GEARS:
			{
			}
			break;
		}
	}

public:
	void setRunSimu(bool runsim)
	{
		EditDlg.SetMinimized(runsim);
		brunsimu=runsim;
	};
	CarSim()
	{
		brunsimu=false;
	};
	bool brunsimu;
	VehicleEdit vedit;
	VehicleSimu	vsimu;
	UIDialog EditDlg;
};


#define _WW 10
#define _HH 20
RenderDevice *RD;

void CALLBACK uicbproc( UINT nEvent, int nControlID, UIControl* pControl ,void * mdata)
{
	CarSim *sim=(CarSim*)mdata;
	switch(nEvent)
	{
	case EVENT_SLIDER_VALUE_CHANGED:
		{
			if(nControlID==8)//pacejka a,b,c
			{
				UISlider *sld=(UISlider*)pControl;
				float value=(float)(sld->GetValue())/10.0f;
				UIComboBox *cob=sim->EditDlg.GetComboBox(7);
				UIStatic *stc=sim->EditDlg.GetStatic(23);
				VehicleEdit::PaceJkaPara *para=(VehicleEdit::PaceJkaPara*)(cob->GetSelectedData());

				*para->value=value;

				char txt[128];
				sprintf(txt,"%s:  %.3f",para->name.c_str(),value);
				stc->SetText(txt);
			}
			else if(nControlID==9)//load
			{
				UISlider *sld=(UISlider*)pControl;
				UIStatic *stc=sim->EditDlg.GetStatic(19);
				float value=sld->GetValue();

				char txt[128];
				sprintf(txt,"%s %.3f","Load:",value);
				stc->SetText(txt);

				sim->vedit.pacejka.SetNormalForce(value);

			}
			else if(nControlID==10)//camber
			{
				UISlider *sld=(UISlider*)pControl;
				UIStatic *stc=sim->EditDlg.GetStatic(20);
				float value=sld->GetValue();

				char txt[128];
				sprintf(txt,"%s %.3f","Camber:",value);
				stc->SetText(txt);
				float rad10cvt=0.174532925f/10.0f;
				sim->vedit.pacejka.SetCamber(-value * rad10cvt);
			}
			else if(nControlID==17)//traction
			{
				UISlider *sld=(UISlider*)pControl;
				UIStatic *stc=sim->EditDlg.GetStatic(24);
				UIComboBox *cob=sim->EditDlg.GetComboBox(18);
				float value=(float)(sld->GetValue())/100.0f;
				VehicleEdit::DataPara *udt=(VehicleEdit::DataPara*)cob->GetSelectedData();
				if(udt==NULL)break;

				*udt->value=value;

				char txt[128];
				sprintf(txt,"%s %.3f",udt->name.c_str(),value);
				stc->SetText(txt);
				
				sim->vedit.traction.reCreate(&(sim->vedit.crv),5);

			}
			else if(nControlID>=55 && nControlID<=61)	//masspart edit
			{
				UISlider *sld=(UISlider*)pControl;
				float value=(float)(sld->GetValue())/100.0f;
				UIComboBox *cob=sim->EditDlg.GetComboBox(29);
				UIStatic *stc=sim->EditDlg.GetStatic(nControlID+14);
				VehicleEdit::DataPara *para=(VehicleEdit::DataPara*)(cob->GetSelectedData()) + (nControlID-55);

				*para->value=value;

				char txt[128];
				sprintf(txt,"%s: %.3f",para->name.c_str(),value);
				stc->SetText(txt);
			}
			else if(nControlID>=46 && nControlID<=54)	//assist
			{
				UISlider *sld=(UISlider*)pControl;
				float value=(float)(sld->GetValue())/100.0f;
				int ofst,comid;
				if(nControlID>=46 && nControlID<=48)
				{
					ofst=(nControlID-46);
					comid=26;
				}
				else if(nControlID>=49 && nControlID<=51)
				{
					ofst=(nControlID-49);
					comid=27;
				}
				else if(nControlID>=52 && nControlID<=54)
				{
					ofst=(nControlID-52);
					comid=28;
				}
				UIComboBox *cob=sim->EditDlg.GetComboBox(comid);
				UIStatic *stc=sim->EditDlg.GetStatic(nControlID+10);
				VehicleEdit::DataPara *para=(VehicleEdit::DataPara*)(cob->GetSelectedData()) + ofst;

				*para->value=value;

				char txt[128];
				sprintf(txt,"%s: %.3f",para->name.c_str(),value);
				stc->SetText(txt);
			}
			else if(nControlID>=30 && nControlID<=35) //wheelsus
			{
				UISlider *sld=(UISlider*)pControl;
				float value=(float)(sld->GetValue())/100.0f;
				int ofst,comid;
				if(nControlID>=30 && nControlID<=32)
				{
					ofst=(nControlID-30);
					comid=20;
				}
				else if(nControlID>=33 && nControlID<=35)
				{
					ofst=(nControlID-33);
					comid=21;
				}
				UIComboBox *cob=sim->EditDlg.GetComboBox(comid);
				UIStatic *stc=sim->EditDlg.GetStatic(nControlID+10);
				VehicleEdit::DataPara *para=(VehicleEdit::DataPara*)(cob->GetSelectedData()) + ofst;

				*para->value=value;

				char txt[128];
				sprintf(txt,"%s: %.3f",para->name.c_str(),value);
				stc->SetText(txt);
				
			}
			else if(nControlID>=36 && nControlID<=45) //transmission
			{
				UISlider *sld=(UISlider*)pControl;
				float value=(float)(sld->GetValue())/100.0f;
				int ofst,comid;
				if(nControlID>=36 && nControlID<=38)
				{
					ofst=(nControlID-36);
					comid=22;
				}
				else if(nControlID>=39 && nControlID<=41)
				{
					ofst=(nControlID-39);
					comid=23;
				}
				else if(nControlID>=42 && nControlID<=44)
				{
					ofst=(nControlID-42);
					comid=24;
				}
				else if(nControlID==45)
				{
					ofst=(nControlID-45);
					comid=25;
				}

				UIComboBox *cob=sim->EditDlg.GetComboBox(comid);
				UIStatic *stc=sim->EditDlg.GetStatic(nControlID+10);
				VehicleEdit::DataPara *para=(VehicleEdit::DataPara*)(cob->GetSelectedData()) + ofst;

				*para->value=value;

				char txt[128];
				sprintf(txt,"%s: %.3f",para->name.c_str(),value);
				stc->SetText(txt);
				
			}

		}
		break;
	case EVENT_COMBOBOX_SELECTION_CHANGED:
		{
			if(nControlID==16)//fx,fy,mz
			{
				UIComboBox *cob=(UIComboBox*)pControl;
				UIComboBoxItem *it=cob->GetSelectedItem();

				UIComboBox *paraCob=sim->EditDlg.GetComboBox(7);

				if(!strcmp(it->strText," Fx"))
				{
					paraCob->RemoveAllItems();
					for(int i=0;i<13;i++)
					{
						paraCob->AddItem(sim->vedit.b[i].name.c_str(),(void*)(&sim->vedit.b[i]));
					}
				}
				else if(!strcmp(it->strText," Fy"))
				{
					paraCob->RemoveAllItems();
					for(int i=0;i<15;i++)
					{
						paraCob->AddItem(sim->vedit.a[i].name.c_str(),(void*)(&sim->vedit.a[i]));
					}
				}
				else if(!strcmp(it->strText," Mz"))
				{
					paraCob->RemoveAllItems();
					for(int i=0;i<18;i++)
					{
						paraCob->AddItem(sim->vedit.c[i].name.c_str(),(void*)(&sim->vedit.c[i]));
					}
				}
			}
			else if(nControlID==7)//para a,b,c
			{
				UIComboBox *cb=(UIComboBox*)pControl;
				VehicleEdit::PaceJkaPara *udt=(VehicleEdit::PaceJkaPara *)(cb->GetSelectedData());
				if(udt==NULL)break;
				UIStatic *st=sim->EditDlg.GetStatic(23);
				UISlider *sld=sim->EditDlg.GetSlider(8);

				char txt[128];
				sprintf(txt,"%s:  %.3f", (char*)(udt->name.c_str()),*udt->value);
				st->SetText(txt);

				sld->SetRange(udt->min*10, udt->max*10);
				sld->SetValue( *udt->value*10 );

				UIEditBox *ei=sim->EditDlg.GetEditBox(24);
				ei->SetText((char*)(udt->desc.c_str()));

			}
			else if(nControlID==18)//traction para
			{
				UIComboBox *cb=(UIComboBox*)pControl;
				VehicleEdit::DataPara *udt=(VehicleEdit::DataPara *)(cb->GetSelectedData());
				if(udt==NULL)break;
				UIStatic *st=sim->EditDlg.GetStatic(24);
				UISlider *sld=sim->EditDlg.GetSlider(17);
				
				char txt[128];
				sprintf(txt,"%s %.3f", (char*)(udt->name.c_str()), *udt->value);
				st->SetText(txt);

				sld->SetRange(udt->min*100, udt->max*100);
				sld->SetValue( *udt->value*100);
			}
			else if(nControlID==29)//weightdist
			{
				UIComboBox *cb=(UIComboBox*)pControl;
				VehicleEdit::DataPara *udt=(VehicleEdit::DataPara *)(cb->GetSelectedData());
				int dnum=cb->GetDataNum();
				for(int i=0;i<dnum;i++)
				{
					UIStatic *st=sim->EditDlg.GetStatic(69+i);
					UISlider *sld=sim->EditDlg.GetSlider(55+i);
					VehicleEdit::DataPara *u=udt+i;

					char txt[128];
					sprintf(txt,"%s:%.3f",(char*)(u->name.c_str()),u->value);
					st->SetText(txt);

					sld->SetRange(u->min*100,u->max*100);
					sld->SetValue(*u->value*100);
				}
			}
			else if(nControlID>=26 && nControlID<=28)//assist
			{
				UIComboBox *cb=(UIComboBox*)pControl;
				VehicleEdit::DataPara *udt=(VehicleEdit::DataPara *)(cb->GetSelectedData());
				int dnum=cb->GetDataNum();
				int stid,slid;
				if(nControlID==26)
				{
					stid=56;
					slid=46;
				}
				else if(nControlID==27)
				{
					stid=59;
					slid=49;
				}
				else if(nControlID==28)
				{
					stid=62;
					slid=52;
					for(int j=0;j<2;j++)
					{
						for(int i=0;i<3;i++)
						{
							UIStatic *st=sim->EditDlg.GetStatic(stid+i+j*100);
							UISlider *sld=sim->EditDlg.GetSlider(slid+i+j*100);
							VehicleEdit::DataPara *u=udt+i;

							char txt[128];
							sprintf(txt,"%s:%.3f",(char*)(u->name.c_str()),u->value);
							st->SetText(txt);

							sld->SetRange(u->min*100,u->max*100);
							sld->SetValue(*(u->value)*100);
						}
					}

				}
				if(nControlID!=28)
				{
					for(int i=0;i<dnum;i++)
					{
						UIStatic *st=sim->EditDlg.GetStatic(stid+i);
						UISlider *sld=sim->EditDlg.GetSlider(slid+i);
						VehicleEdit::DataPara *u=udt+i;

						char txt[128];
						sprintf(txt,"%s:%.3f",(char*)(u->name.c_str()),u->value);
						st->SetText(txt);

						sld->SetRange(u->min*100,u->max*100);
						sld->SetValue(*(u->value)*100);
					}
				}
			}
			else if(nControlID>=20 && nControlID<=21)//wheelsus
			{
				UIComboBox *cb=(UIComboBox*)pControl;
				VehicleEdit::DataPara *udt=(VehicleEdit::DataPara *)(cb->GetSelectedData());
				int dnum=cb->GetDataNum();
				int stid,slid;
				if(nControlID==20)
				{
					stid=40;
					slid=30;
				}
				else if(nControlID==21)
				{
					stid=43;
					slid=33;
				}
				for(int i=0;i<dnum;i++)
				{
					UIStatic *st=sim->EditDlg.GetStatic(stid+i);
					UISlider *sld=sim->EditDlg.GetSlider(slid+i);
					VehicleEdit::DataPara *u=udt+i;

					char txt[128];
					sprintf(txt,"%s:%.3f",(char*)(u->name.c_str()),u->value);
					st->SetText(txt);

					sld->SetRange(u->min*100,u->max*100);
					sld->SetValue(*(u->value)*100);
				}
			}
			else if(nControlID>=22 && nControlID<=25)//transmision
			{
				UIComboBox *cb=(UIComboBox*)pControl;
				VehicleEdit::DataPara *udt=(VehicleEdit::DataPara *)(cb->GetSelectedData());
				int dnum=cb->GetDataNum();
				int stid,slid;
				if(nControlID==22)
				{
					stid=46;
					slid=36;
				}
				else if(nControlID==23)
				{
					stid=49;
					slid=39;
				}
				else if(nControlID==24)
				{
					stid=52;
					slid=42;
				}
				else if(nControlID==25)
				{
					stid=55;
					slid=45;
				}
				for(int i=0;i<dnum;i++)
				{
					UIStatic *st=sim->EditDlg.GetStatic(stid+i);
					UISlider *sld=sim->EditDlg.GetSlider(slid+i);
					VehicleEdit::DataPara *u=udt+i;

					char txt[128];
					sprintf(txt,"%s:%.3f",(char*)(u->name.c_str()),u->value);
					st->SetText(txt);

					sld->SetRange(u->min*100,u->max*100);
					sld->SetValue(*(u->value)*100);
				}
			}
		}
		break;
	case EVENT_BUTTON_CLICKED:
		{
			if(nControlID==2)//save
			{
				sim->vedit.saveCurve("Save.txt");
			}
			else if(nControlID==1)//load
			{
				sim->vedit.loadCurve("Save.txt");
			}
			else if(nControlID==14)//clear
			{
				sim->vedit.clear();
			}
		}
		break;
	case EVENT_CHECKBOX_CHANGED:
		{
			if(nControlID==15)//leastsquarefit
			{
				UICheckBox *chk=(UICheckBox*)pControl;
				if(chk->GetChecked())
					sim->vedit.crv.setFitingType(LEASTSQUARE);
				else sim->vedit.crv.setFitingType(LINEAR);
			}
		}
		break;
	case EVENT_RADIOBUTTON_CHANGED:
		{
			sim->setRunSimu(false);
			switch(nControlID)
			{
			case 3://pacejka
				{
					sim->vedit.setEditMode(PACEJKA);
					sim->setEditPara(WHEELSUS,false);
					sim->setEditPara(WEIGHTDIST,false);
					sim->setEditPara(ASSIST,false);
					sim->setEditPara(TRANSMISS,false);
					sim->setEditPara(TORQUE,false);
					sim->setEditPara(TRACTION,false);
					sim->setEditPara(CURVE,false);
					sim->setEditPara(PACEJKA,true);
				}
				break;
			case 4://torque
				{
					sim->vedit.setEditMode(TORQUE);
					sim->setEditPara(WHEELSUS,false);
					sim->setEditPara(WEIGHTDIST,false);
					sim->setEditPara(ASSIST,false);
					sim->setEditPara(TRANSMISS,false);
					sim->setEditPara(PACEJKA,false);
					sim->setEditPara(TRACTION,false);
					sim->setEditPara(CURVE,false);
					sim->setEditPara(TORQUE,true);
				}
				break;
			case 5://traction
				{
					sim->vedit.setEditMode(TRACTION);
					sim->setEditPara(WHEELSUS,false);
					sim->setEditPara(WEIGHTDIST,false);
					sim->setEditPara(ASSIST,false);
					sim->setEditPara(TRANSMISS,false);
					sim->setEditPara(PACEJKA,false);
					sim->setEditPara(TORQUE,false);
					sim->setEditPara(CURVE,false);
					sim->setEditPara(TRACTION,true);
				}				
				break;
			case 6://curve
				{
					sim->vedit.setEditMode(CURVE);
					sim->setEditPara(WHEELSUS,false);
					sim->setEditPara(WEIGHTDIST,false);
					sim->setEditPara(ASSIST,false);
					sim->setEditPara(TRANSMISS,false);
					sim->setEditPara(PACEJKA,false);
					sim->setEditPara(TORQUE,false);
					sim->setEditPara(TRACTION,false);
					sim->setEditPara(CURVE,true);
				}
				break;
			case 26://torque
					sim->vedit.setTorqueOrConsumption(0);
				break;
			case 27://consumption
					sim->vedit.setTorqueOrConsumption(1);
				break;
			case 30://Gearbox
				{
					sim->vedit.setEditMode(GEARS);
					sim->setEditPara(WHEELSUS,false);
					sim->setEditPara(WEIGHTDIST,false);
					sim->setEditPara(ASSIST,false);
					sim->setEditPara(TRANSMISS,false);
					sim->setEditPara(PACEJKA,false);
					sim->setEditPara(TORQUE,false);
					sim->setEditPara(TRACTION,false);
					sim->setEditPara(CURVE,false);
				}
				break;
			case 31://WeightDist
				{
					sim->vedit.setEditMode(WEIGHTDIST);
					sim->setEditPara(PACEJKA,false);
					sim->setEditPara(TORQUE,false);
					sim->setEditPara(TRACTION,false);
					sim->setEditPara(CURVE,false);
					sim->setEditPara(WHEELSUS,false);
					sim->setEditPara(ASSIST,false);
					sim->setEditPara(TRANSMISS,false);
					sim->setEditPara(WEIGHTDIST,true);
				}
				break;
			case 32://Wheel+Sus
				{
					sim->vedit.setEditMode(WHEELSUS);
					sim->setEditPara(PACEJKA,false);
					sim->setEditPara(TORQUE,false);
					sim->setEditPara(TRACTION,false);
					sim->setEditPara(CURVE,false);
					sim->setEditPara(WEIGHTDIST,false);
					sim->setEditPara(ASSIST,false);
					sim->setEditPara(TRANSMISS,false);
					sim->setEditPara(WHEELSUS,true);
				}
				break;
			case 33://Transmiss
				{
					sim->vedit.setEditMode(TRANSMISS);
					sim->setEditPara(PACEJKA,false);
					sim->setEditPara(TORQUE,false);
					sim->setEditPara(TRACTION,false);
					sim->setEditPara(CURVE,false);
					sim->setEditPara(WHEELSUS,false);
					sim->setEditPara(WEIGHTDIST,false);
					sim->setEditPara(ASSIST,false);
					sim->setEditPara(TRANSMISS,true);
				}
				break;
			case 34: //Assist
				{
					sim->vedit.setEditMode(ASSIST);
					sim->setEditPara(PACEJKA,false);
					sim->setEditPara(TORQUE,false);
					sim->setEditPara(TRACTION,false);
					sim->setEditPara(CURVE,false);
					sim->setEditPara(WHEELSUS,false);
					sim->setEditPara(WEIGHTDIST,false);
					sim->setEditPara(TRANSMISS,false);
					sim->setEditPara(ASSIST,true);
				}
				break;
			case 35://Mapedit
				{
					sim->vedit.setEditMode(MAPEDIT);
					sim->setEditPara(PACEJKA,false);
					sim->setEditPara(TORQUE,false);
					sim->setEditPara(TRACTION,false);
					sim->setEditPara(CURVE,false);
					sim->setEditPara(WHEELSUS,false);
					sim->setEditPara(WEIGHTDIST,false);
					sim->setEditPara(ASSIST,false);
					sim->setEditPara(TRANSMISS,false);
				}
				break;

			case 36://runsimu
				sim->setRunSimu(true);
				break;
			}
		}
		break;
	}
}





void CarSim::gameinit()
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
	
	DefInit3D();
	RD=GetRenderDev();


	EditDlg.SetLocation(20,20);
	EditDlg.SetSize(760,550);
	EditDlg.SetCaptionHeight(10);
	EditDlg.EnableCaption(true);
	EditDlg.SetCaptionText("Configeration");
	EditDlg.SetCallback(uicbproc,(void*)this);
	EditDlg.SetRefreshTime(20000);

	int xx=0;
	int yy=0;
	EditDlg.AddButton(1,"  Load", 70+xx,496+yy , 58,20);
	EditDlg.AddButton(2,"  Save", 10+xx,496+yy , 58,20);
	EditDlg.AddButton(14," Clear", 10+xx,470+yy , 58,20);

	EditDlg.AddRadioButton(3,0,"PaceJka",	 10+xx,10+yy , 10,10,true);
	EditDlg.AddRadioButton(4,0,"Torque",	 10+xx,30+yy , 10,10);
	EditDlg.AddRadioButton(5,0,"Traction",	 10+xx,50+yy , 10,10);
	EditDlg.AddRadioButton(6,0,"Curve",		 10+xx,70+yy , 10,10);
	EditDlg.AddRadioButton(30,0,"Gearbox", 10+xx,90+yy,10,10);
	EditDlg.AddRadioButton(31,0,"WeightDist", 10+xx,110+yy,10,10);
	EditDlg.AddRadioButton(32,0,"Wheel+Sus", 10+xx,130+yy,10,10);
	EditDlg.AddRadioButton(33,0,"Transmiss", 10+xx,150+yy,10,10);
	EditDlg.AddRadioButton(34,0,"Assist", 10+xx,170+yy,10,10);
	EditDlg.AddRadioButton(35,0,"MapEdit", 10+xx,190+yy,10,10);
	EditDlg.AddRadioButton(36,0,"RunSimu", 10+xx,210+yy,10,10);


	EditDlg.AddCheckBox(15,"LeastSquareFit",10+xx,90+yy+140, 10,10);


	EditDlg.AddComboBox(7, 70+xx,230+yy+140, 56,18);
	for(int i=0;i<13;i++)
	{
		EditDlg.GetComboBox(7)->AddItem(vedit.b[i].name.c_str(),(void*)(&vedit.b[i]));
	}
	EditDlg.AddComboBox(16,10+xx,230+yy+140,50,18);
	EditDlg.GetComboBox(16)->SetDropHeight(32);
	EditDlg.GetComboBox(16)->AddItem(" Fx",0);
	EditDlg.GetComboBox(16)->AddItem(" Fy",0);
	EditDlg.GetComboBox(16)->AddItem(" Mz",0);

	EditDlg.AddComboBox(17,10+xx,230+yy+170,50,18);
	EditDlg.GetComboBox(17)->SetDropHeight(40);
	EditDlg.GetComboBox(17)->AddItem(" FL",0);
	EditDlg.GetComboBox(17)->AddItem(" FR",0);
	EditDlg.GetComboBox(17)->AddItem(" RL",0);
	EditDlg.GetComboBox(17)->AddItem(" RR",0);

	EditDlg.AddSlider(8, 10+xx,210+yy+140,116,10);//pacejka para a,b,c

	EditDlg.AddSlider(9, 10+xx,110+yy+140,116,10);//load
	EditDlg.AddSlider(10,10+xx,135+yy+140,116,10);//camber
	EditDlg.GetSlider(9)->SetRange(0,10000);
	EditDlg.GetSlider(9)->SetValue(vedit.pacejka.GetFz()*1000);
	EditDlg.GetSlider(10)->SetRange(-10,10);
	EditDlg.GetSlider(10)->SetValue(vedit.pacejka.GetCamber());

	EditDlg.AddSlider(11,10+xx,160+yy+140,116,10);//slipratio
	EditDlg.AddSlider(12,10+xx,185+yy+140,116,10);//slipangel

	EditDlg.AddStatic(19,"Load: 2500",		10+xx,110+yy-10+140,50,10);
	EditDlg.AddStatic(20,"Camber: 0.0",		10+xx,135+yy-10+140,50,10);
	EditDlg.AddStatic(21,"SlipRatio: 0.0",	10+xx,160+yy-10+140,50,10);
	EditDlg.AddStatic(22,"SlipAngle: 0.0",	10+xx,185+yy-10+140,50,10);
	EditDlg.AddStatic(23,"Para: 0.0",		10+xx,210+yy-10+140,50,10);


	EditDlg.AddStatic(24,"Para: 0.0",	10+xx,118+yy-10+140,50,10);
	EditDlg.AddSlider(17,10+xx,118+yy+140,100,10);//traction para
	EditDlg.AddComboBox(18,10+xx,135+yy+140,68,18);
	EditDlg.GetComboBox(18)->AddItem(vedit.A.name.c_str(),(void*)(&vedit.A));
	EditDlg.GetComboBox(18)->AddItem(vedit.Cd.name.c_str(),(void*)(&vedit.Cd));
	EditDlg.GetComboBox(18)->AddItem(vedit.transmissionef.name.c_str(),(void*)(&vedit.transmissionef));
	EditDlg.GetComboBox(18)->AddItem(vedit.wheelrad.name.c_str(),(void*)(&vedit.wheelrad));
	EditDlg.GetComboBox(18)->AddItem(vedit.weight.name.c_str(),(void*)(&vedit.weight));
	EditDlg.GetComboBox(18)->AddItem(vedit.rollcoef.name.c_str(), (void*)(&vedit.rollcoef));
	EditDlg.GetComboBox(18)->AddItem(vedit.ig0.name.c_str(),(void*)(&vedit.ig0));
	EditDlg.GetComboBox(18)->AddItem(vedit.ig[1].name.c_str(),(void*)(&vedit.ig[1]));
	EditDlg.GetComboBox(18)->AddItem(vedit.ig[2].name.c_str(),(void*)(&vedit.ig[2]));
	EditDlg.GetComboBox(18)->AddItem(vedit.ig[3].name.c_str(),(void*)(&vedit.ig[3]));
	EditDlg.GetComboBox(18)->AddItem(vedit.ig[4].name.c_str(),(void*)(&vedit.ig[4]));
	EditDlg.GetComboBox(18)->AddItem(vedit.ig[5].name.c_str(),(void*)(&vedit.ig[5]));

	EditDlg.AddEditBox(24,"",178,500,544,24);

	EditDlg.AddRadioButton(26,1, "Torque / Power", 10,120+140, 10,10);
	EditDlg.AddRadioButton(27,1, "Fuel Consumption", 10,140+140, 10,10);
	EditDlg.GetRadioButton(26)->SetChecked(true);

	/////
	//wheel+susp

	EditDlg.AddComboBox(20,200,100,150,18);		//wheel, tyre
	EditDlg.GetComboBox(20)->SetDropHeight(40);
	EditDlg.GetComboBox(20)->AddItem("wheelpos",(void*)(vedit.wheelposfl),3);
	EditDlg.GetComboBox(20)->AddItem("wheelsize",(void*)(vedit.wheelsizef),3);
	EditDlg.GetComboBox(20)->AddItem("tyre",(void*)(vedit.wheeltyref),3);


	EditDlg.AddStatic(40,"Para: 0.0",200,130,150,10);
	EditDlg.AddStatic(41,"Para: 0.0",200,155,150,10);
	EditDlg.AddStatic(42,"Para: 0.0",200,180,150,10);
	EditDlg.AddSlider(30,200,140,150,10); //x
	EditDlg.AddSlider(31,200,165,150,10); //y
	EditDlg.AddSlider(32,200,190,150,10); //z

	EditDlg.AddComboBox(21,200,210+100,150,18);		//sus,toecamber,arb
	EditDlg.GetComboBox(21)->SetDropHeight(50);
	EditDlg.GetComboBox(21)->AddItem("susaxis",(void*)(vedit.susaxisf),3);
	EditDlg.GetComboBox(21)->AddItem("springdamp",(void*)(vedit.susspringdampf),2);
	EditDlg.GetComboBox(21)->AddItem("arb",(void*)(vedit.susarbf),2);
	EditDlg.GetComboBox(21)->AddItem("toecamber",(void*)(vedit.sustoecamber),2);

	EditDlg.AddStatic(43,"Para: 0.0",200,240+100,150,10);
	EditDlg.AddStatic(44,"Para: 0.0",200,265+100,150,10);
	EditDlg.AddStatic(45,"Para: 0.0",200,290+100,150,10);
	EditDlg.AddSlider(33,200,250+100,150,10); //x
	EditDlg.AddSlider(34,200,275+100,150,10); //y
	EditDlg.AddSlider(35,200,300+100,150,10); //z

	//transmiss
	EditDlg.AddComboBox(22,200,100,180,18);		//gear autochangeup/down
	EditDlg.GetComboBox(22)->SetDropHeight(20);
	EditDlg.GetComboBox(22)->AddItem("changupdown",(void*)(vedit.gearchangupdown),2);

	EditDlg.AddStatic(46,"Para: 0.0",200,130,180,10);
	EditDlg.AddStatic(47,"Para: 0.0",200,155,180,10);
	EditDlg.AddStatic(48,"Para: 0.0",200,180,180,10);
	EditDlg.AddSlider(36,200,140,180,10); //x
	EditDlg.AddSlider(37,200,165,180,10); //y
	EditDlg.AddSlider(38,200,190,180,10); //z

	EditDlg.AddComboBox(23,200,210+60,180,18);		//traction,differentials,clutch
	EditDlg.GetComboBox(23)->SetDropHeight(40);
	EditDlg.GetComboBox(23)->AddItem("tractiondiff",(void*)(vedit.tramtractiondiff),2);
	EditDlg.GetComboBox(23)->AddItem("clutch",(void*)(vedit.tramclutch),3);

	EditDlg.AddStatic(49,"Para: 0.0",200,240+60,180,10);
	EditDlg.AddStatic(50,"Para: 0.0",200,265+60,180,10);
	EditDlg.AddStatic(51,"Para: 0.0",200,290+60,180,10);
	EditDlg.AddSlider(39,200,250+60,180,10); //x
	EditDlg.AddSlider(40,200,275+60,180,10); //y
	EditDlg.AddSlider(41,200,300+60,180,10); //z

	EditDlg.AddComboBox(24,200+270,320-140,180,18);		//brake
	EditDlg.GetComboBox(24)->SetDropHeight(20);
	EditDlg.GetComboBox(24)->AddItem("brake",(void*)(vedit.bsbrake),3);

	EditDlg.AddStatic(52,"Para: 0.0",200+270,350-140,180,10);
	EditDlg.AddStatic(53,"Para: 0.0",200+270,375-140,180,10);
	EditDlg.AddStatic(54,"Para: 0.0",200+270,400-140,180,10);
	EditDlg.AddSlider(42,200+270,360-140,180,10); //x
	EditDlg.AddSlider(43,200+270,385-140,180,10); //y
	EditDlg.AddSlider(44,200+270,410-140,180,10); //z

	EditDlg.AddComboBox(25,400+70,100,180,18);		//steer
	EditDlg.GetComboBox(25)->SetDropHeight(20);
	EditDlg.GetComboBox(25)->AddItem("steer",(void*)(vedit.bssteer),1);
	EditDlg.AddStatic(55,"Para: 0.0",400+70,130,180,10);
	EditDlg.AddSlider(45,400+70,140,180,10); //x


	//assist
	EditDlg.AddComboBox(26,200,100,140,18);		//steeringwheel
	EditDlg.GetComboBox(26)->SetDropHeight(20);
	EditDlg.GetComboBox(26)->AddItem("steeringwheel",(void*)(vedit.steeringwheel),3);

	EditDlg.AddStatic(56,"Para: 0.0",200,130,140,10);
	EditDlg.AddStatic(57,"Para: 0.0",200,155,140,10);
	EditDlg.AddStatic(58,"Para: 0.0",200,180,140,10);
	EditDlg.AddSlider(46,200,140,140,10); //x
	EditDlg.AddSlider(47,200,165,140,10); //y
	EditDlg.AddSlider(48,200,190,140,10); //z

	EditDlg.AddComboBox(27,200,210+20,140,18);		//throttlepadel,brakepadel,clutchpadel
	EditDlg.GetComboBox(27)->SetDropHeight(40);
	EditDlg.GetComboBox(27)->AddItem("throttle",(void*)(vedit.throttle),3);
	EditDlg.GetComboBox(27)->AddItem("brake",(void*)(vedit.brake),3);
	EditDlg.GetComboBox(27)->AddItem("clutch",(void*)(vedit.clutch),3);

	EditDlg.AddStatic(59,"Para: 0.0",200,240+20,140,10);
	EditDlg.AddStatic(60,"Para: 0.0",200,265+20,140,10);
	EditDlg.AddStatic(61,"Para: 0.0",200,290+20,140,10);
	EditDlg.AddSlider(49,200,250+20,140,10); //x
	EditDlg.AddSlider(50,200,275+20,140,10); //y
	EditDlg.AddSlider(51,200,300+20,140,10); //z

	EditDlg.AddComboBox(28,200+260,100,140,18);		//camera
	EditDlg.GetComboBox(28)->SetDropHeight(40);
	EditDlg.GetComboBox(28)->AddItem("Camera0",(void*)(vedit.camera0),6);
	EditDlg.GetComboBox(28)->AddItem("Camera1",(void*)(vedit.camera1),6);
	EditDlg.GetComboBox(28)->AddItem("Camera2",(void*)(vedit.camera2),6);
	EditDlg.GetComboBox(28)->AddItem("Camera3",(void*)(vedit.camera3),6);
	EditDlg.GetComboBox(28)->AddItem("Camera4",(void*)(vedit.camera4),6);

	EditDlg.AddStatic(62,"Para: 0.0",200+260,130,140,10);
	EditDlg.AddStatic(63,"Para: 0.0",200+260,155,140,10);
	EditDlg.AddStatic(64,"Para: 0.0",200+260,180,140,10);
	EditDlg.AddSlider(52,200+260,140,140,10); //x
	EditDlg.AddSlider(53,200+260,165,140,10); //y
	EditDlg.AddSlider(54,200+260,190,140,10); //z

	EditDlg.AddStatic(162,"Para: 0.0",200+260,150+60,140,10);
	EditDlg.AddStatic(163,"Para: 0.0",200+260,175+60,140,10);
	EditDlg.AddStatic(164,"Para: 0.0",200+260,200+60,140,10);
	EditDlg.AddSlider(152,200+260,160+60,140,10); //x
	EditDlg.AddSlider(153,200+260,185+60,140,10); //y
	EditDlg.AddSlider(154,200+260,210+60,140,10); //z


	EditDlg.AddCheckBox(20,"PreventFlip",200+260,320, 10,10);
	EditDlg.AddCheckBox(21,"Enable ABS",200+260,340, 10,10);
	EditDlg.AddCheckBox(22,"Enable ESP",200+260,360, 10,10);
	EditDlg.AddCheckBox(23,"Enable TSC",200+260,380, 10,10);


	//weight+dist
	EditDlg.AddStatic(200,"Vehicle Name",				200,100-20,100,10);
	EditDlg.AddStatic(201,"LeastTurnningRadius: 0.0",	200,120-20,100,10);
	EditDlg.AddStatic(202,"RideHeight: 0.0",			200,140-20,100,10);
	EditDlg.AddStatic(203,"WheelBase: 0.0",				200,160-20,100,10);
	EditDlg.AddStatic(204,"TotleMass: 0.0",				200,180-20,100,10);
	EditDlg.AddStatic(205,"VehicleType: 0.0",			200,200-20,100,10);
	EditDlg.AddStatic(206,"MaxSpeed: 0.0",				200,220-20,100,10);
	EditDlg.AddStatic(207,"MaxTorque: 0.0",				200,240-20,100,10);
	EditDlg.AddStatic(208,"MaxClimbe: 0.0",				200,260-20,100,10);
	EditDlg.AddStatic(209,"FlipDegree: 0.0",			200,280-20,100,10);


	EditDlg.AddComboBox(29,200,260+100,150,18);		//masspart
	EditDlg.GetComboBox(29)->SetDropHeight(50);
	EditDlg.GetComboBox(29)->AddItem("main",(void*)(vedit.masspartmain),7);
	EditDlg.GetComboBox(29)->AddItem("chassis",(void*)(vedit.masspartchassis),7);
	EditDlg.GetComboBox(29)->AddItem("middle",(void*)(vedit.masspartmiddle),7);
	EditDlg.GetComboBox(29)->AddItem("front",(void*)(vedit.masspartfront),7);
	EditDlg.GetComboBox(29)->AddItem("rear",(void*)(vedit.masspartrear),7);
	EditDlg.GetComboBox(29)->AddItem("engine",(void*)(vedit.masspartengin),7);

	EditDlg.AddStatic(69,"Para: 0.0",200,290+100, 150 ,10);
	EditDlg.AddStatic(70,"Para: 0.0",200,315+100, 150 ,10);
	EditDlg.AddStatic(71,"Para: 0.0",200,340+100, 150 ,10);
	EditDlg.AddSlider(55,200,300+100,150,10);
	EditDlg.AddSlider(56,200,325+100,150,10);
	EditDlg.AddSlider(57,200,350+100,150,10);

	EditDlg.AddStatic(72,"Para: 0.0",200+200,390-20, 150 ,10);
	EditDlg.AddStatic(73,"Para: 0.0",200+200,415-20, 150 ,10);
	EditDlg.AddStatic(74,"Para: 0.0",200+200,440-20, 150 ,10);
	EditDlg.AddSlider(58,200+200,400-20,150,10);
	EditDlg.AddSlider(59,200+200,425-20,150,10);
	EditDlg.AddSlider(60,200+200,450-20,150,10);

	EditDlg.AddStatic(75,"Para: 0.0",200+200,465-20,150,10);
	EditDlg.AddSlider(61,200+200,475-20,150,10);

/////
	EditDlg.GetComboBox(7)->SetSelectedByIndex(0);
	EditDlg.GetComboBox(16)->SetSelectedByIndex(0);
	EditDlg.GetComboBox(18)->SetSelectedByIndex(0);
	EditDlg.GetComboBox(20)->SetSelectedByIndex(0);
	EditDlg.GetComboBox(21)->SetSelectedByIndex(0);
	EditDlg.GetComboBox(22)->SetSelectedByIndex(0);
	EditDlg.GetComboBox(23)->SetSelectedByIndex(0);
	EditDlg.GetComboBox(24)->SetSelectedByIndex(0);
	EditDlg.GetComboBox(25)->SetSelectedByIndex(0);
	EditDlg.GetComboBox(26)->SetSelectedByIndex(0);
	EditDlg.GetComboBox(27)->SetSelectedByIndex(0);
	EditDlg.GetComboBox(28)->SetSelectedByIndex(0);
	EditDlg.GetComboBox(29)->SetSelectedByIndex(0);

	/////

	setEditPara(WHEELSUS,false);
	setEditPara(WEIGHTDIST,false);
	setEditPara(ASSIST,false);
	setEditPara(TRANSMISS,false);

	setEditPara(TORQUE,false);
	setEditPara(CURVE,false);
	setEditPara(TRACTION,false);
	setEditPara(PACEJKA,true);


	vedit.setEditMode(PACEJKA);
	vsimu.init(RD);


}


void CarSim::render()
{
	EditDlg.OnRender(0);

	if(!EditDlg.GetMinimized())
	{
		//vsimu.setRunSimu(false);
		POINT pt;
		EditDlg.GetLocation(pt);
		Vector2 org=Vector2(pt.x,pt.y)+Vector2(450,280);
		vedit.setOffset(org);
		vedit.render();
	}

	if(brunsimu && EditDlg.GetMinimized())
	{
		vsimu.render();
	}

}


CarSim carsim;


void DoFrame();



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR szCmdLine, int iCmdShow){
	MSG	msg;

	if(!_m_buf.InitWindow(WIDTH, HEIGHT, "GEngin  -  Vehicle Simulation", hInstance, &hWnd, WndProc, NULL)) return FALSE;
	if(!_m_buf.SetBufferMode(WIDTH, HEIGHT, BPP, FullScreen, &tcf)) return FALSE;

	carsim.gameinit();


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
			switch(msg.message)
			{
			case WM_KEYDOWN:
				keyDown(msg);
				break;
			}


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

#ifdef _DEBUG_ON_RELEASE
int main(int argc,char *argv[])
{
	WinMain(GetModuleHandle(NULL),NULL,GetCommandLine(),WM_SHOWWINDOW);

	return 0;
}
#endif

void DoFrame(){
	if(SwitchMode){
		_m_buf.SetBufferMode(WIDTH, HEIGHT, BPP, FullScreen, &tcf);
		_m_buf.SetWindowSize(WIDTH, HEIGHT);
		_m_buf.SetPalette(NULL);
		_m_buf.RealizePalette();
		SwitchMode = FALSE;
	}
	//if(getkey('P',true))pause=!pause;
	//if(pause)return;

	if(_m_buf.Lock(&_m_bd))
	{
		clearscr();
		carsim.render();

		drawfps();
		_m_buf.Unlock();
	}		
	//fps=gettimetick();
	RD->SysCamera->TransefCameraByKey(false);
	
	_m_buf.UpdateFrontBuffer(FullScreen ? NULL : UFB_STRETCH);	//Call UpdateFrontBuffer while UNLOCKED.
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	carsim.EditDlg.MsgProc(hwnd,iMsg,wParam,lParam);
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
			MouseX = LOWORD(lParam);
			MouseY = HIWORD(lParam);
			lmclked=true;
			carsim.vedit.AddPoint(Vector2(mx,my));
			break;
		case WM_LBUTTONUP:
			{
				lmclked=false;
				carsim.vedit.clearEdit();
			}
			break;
		case WM_RBUTTONDOWN:rmclked=true;break;
		case WM_RBUTTONUP:rmclked=false;break;
		case WM_MOUSEMOVE :
			mx= LOWORD(lParam);
			my= HIWORD(lParam);
			if(lmclked)
			{
				carsim.vedit.editPoint(Vector2(mx,my));
			}
			if(rmclked)
				RD->SysCamera->TransefCameraByMouse((mx-omx)*50,(my-omy)*50,false);//( (mx-omx)*100,(my-omy)*100);

			omx=mx;omy=my;
			break;
		case WM_KEYDOWN :
			{
				_m_wparam=wParam;
				switch(wParam)
				{
				case VK_ESCAPE :
						PostMessage(hwnd, WM_CLOSE, NULL, NULL);
						break;
				case VK_RETURN:
						break;
				case VK_F8 :
						FullScreen = !FullScreen;
						SwitchMode = TRUE;
						break;
				}
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











































