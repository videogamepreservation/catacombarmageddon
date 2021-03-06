/* Catacomb Armageddon Source Code
 * Copyright (C) 1993-2014 Flat Rock Software
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

// C3_PLAY.C

#include "DEF.H"
#pragma hdrstop

/*
=============================================================================

						 LOCAL CONSTANTS

=============================================================================
*/

#if 0
#define MSHOTDAMAGE	2
#define MSHOTSPEED	10000

#define ESHOTDAMAGE	1
#define ESHOTSPEED	5000

#define SSHOTDAMAGE	3
#define SSHOTSPEED	6500

#define RANDOM_ATTACK 20
#endif

/*
=============================================================================

						 GLOBAL VARIABLES

=============================================================================
*/

boolean ShootPlayer (objtype *ob, short obclass, short speed, statetype *state);
void T_ShootPlayer(objtype *ob);

/*
=============================================================================

						 LOCAL VARIABLES

=============================================================================
*/

/*
=============================================================================

						RED DEMON

=============================================================================
*/

void T_RedDemon (objtype *ob);
void T_RedDemonCheckCnt (objtype *ob);

extern	statetype s_red_demonpause;

extern	statetype s_red_demon1;
extern	statetype s_red_demon2;
extern	statetype s_red_demon3;
extern	statetype s_red_demon4;

extern	statetype s_red_demonattack1;
extern	statetype s_red_demonattack2;
extern	statetype s_red_demonattack3;

extern	statetype s_red_demonouch;

extern	statetype s_red_demondie1;
extern	statetype s_red_demondie2;
extern	statetype s_red_demondie3;
extern	statetype s_red_demondie4;

statetype s_red_demonpause = {RED_DEMON1PIC,30,NULL,&s_red_demon2};

statetype s_red_demon1 = {RED_DEMON1PIC,20,T_RedDemon,&s_red_demon2};
statetype s_red_demon2 = {RED_DEMON2PIC,20,T_RedDemon,&s_red_demon3};
statetype s_red_demon3 = {RED_DEMON3PIC,20,T_RedDemon,&s_red_demon4};
statetype s_red_demon4 = {RED_DEMON4PIC,20,T_RedDemon,&s_red_demon1};

statetype s_red_demonattack1 = {RED_DEMONATTACK1PIC,20,NULL,&s_red_demonattack2};
statetype s_red_demonattack2 = {RED_DEMONATTACK2PIC,20,NULL,&s_red_demonattack3};
statetype s_red_demonattack3 = {RED_DEMONATTACK3PIC,30,T_DoDamage,&s_red_demon2};

statetype s_red_demonouch = {RED_DEMONOUCHPIC,30,NULL,&s_red_demon1};

statetype s_red_demondie1 = {RED_DEMONOUCHPIC,9,NULL,&s_red_demondie2};
statetype s_red_demondie2 = {RED_DEMONDIE1PIC,9,T_RedDemonCheckCnt,&s_red_demondie1};
statetype s_red_demondie3 = {RED_DEMONDIE2PIC,20,NULL,&s_red_demondie4};
statetype s_red_demondie4 = {RED_DEMONDIE3PIC,10,NULL,&s_red_demondie4};


/*
===============
=
= SpawnRedDemon
=
===============
*/

void SpawnRedDemon (int tilex, int tiley)
{
	SpawnNewObj(tilex,tiley,&s_red_demon1,PIXRADIUS*35);
	new->obclass = reddemonobj;
	new->speed = 2048;
	new->flags |= of_shootable;
	new->hitpoints = EasyHitPoints(50);
	new->temp1 = 25;
}


/*
===============
=
= T_RedDemon
=
===============
*/

void T_RedDemon (objtype *ob)
{
	if (Chase (ob,true) || (random(1000)<RANDOM_ATTACK))
	{
		ob->state = &s_red_demonattack1;
		ob->ticcount = ob->state->tictime;
		return;
	}
}

/*
===============
=
= T_RedDemonCheckCnt
=
===============
*/

void T_RedDemonCheckCnt (objtype *ob)
{
	ob->temp1--;
	if (!ob->temp1)
	{
		ob->state = &s_red_demondie3;
		ob->ticcount = ob->state->tictime;
	}
}


/*
=============================================================================

							GRELMINAR

=============================================================================
*/


void T_Grelminar (objtype *ob);
void T_GrelminarShoot (objtype *ob);
void T_Grelm_DropKey(objtype *ob);

extern	statetype s_grelpause;

extern	statetype s_grel1;
extern	statetype s_grel2;

extern	statetype s_grelattack1;
extern	statetype s_grelattack2;
extern	statetype s_grelattack3;

extern	statetype s_grelouch;

extern	statetype s_greldie1;
extern	statetype s_greldie2;
extern	statetype s_greldie3;
extern	statetype s_greldie4;
extern	statetype s_greldie5;
extern 	statetype s_greldie5a;
extern	statetype s_greldie6;


statetype s_grelpause = {GREL1PIC,50,NULL,&s_grel2};

statetype s_grel1 = {GREL1PIC,20,T_Grelminar,&s_grel2};
statetype s_grel2 = {GREL2PIC,20,T_Grelminar,&s_grel1};

//statetype s_grelattack1 = {GRELATTACKPIC,20,NULL,&s_grelattack2};
//statetype s_grelattack2 = {GRELATTACKPIC,-1,T_GrelminarShoot,&s_grelattack3};
statetype s_grelattack3 = {GRELATTACKPIC,30,NULL,&s_grelpause};

statetype s_grelouch = {GRELHITPIC,6,NULL,&s_grel1};

statetype s_greldie1 = {GRELDIE1PIC,22,NULL,&s_greldie2};
statetype s_greldie2 = {GRELDIE2PIC,22,NULL,&s_greldie3};
statetype s_greldie3 = {GRELDIE3PIC,22,NULL,&s_greldie4};
statetype s_greldie4 = {GRELDIE4PIC,22,NULL,&s_greldie5};
statetype s_greldie5 = {GRELDIE5PIC,22,NULL,&s_greldie5a};
statetype s_greldie5a = {GRELDIE5PIC,1,T_Grelm_DropKey,&s_greldie6};
statetype s_greldie6 = {GRELDIE6PIC,0,NULL,&s_greldie6};


extern statetype s_gshot1;

statetype s_gshot1 = {SKULL_SHOTPIC,8,T_ShootPlayer,&s_gshot1};

/*
===============
=
= SpawnGrelminar
=
===============
*/

void SpawnGrelminar (int tilex, int tiley)
{
	unsigned Grel_Hard;
	unsigned DropKey;

	SpawnNewObj(tilex,tiley,&s_grel1,PIXRADIUS*35);
	new->obclass = grelmobj;
	new->speed = 2048;
	new->flags |= of_shootable;

	//
	// if Grelminar is to drop a key the info-plane byte to the right
	//		should have a 1 in the highbyte, else he will not drop the key.
	//
	DropKey = *(mapsegs[2]+farmapylookup[tiley]+tilex+1);
	if (DropKey)
		new->temp1 = DropKey>>8;
	else
		new->temp1 = 0;

	//
	// The info-plane byte below Grelminar will determine how powerful
	//		Grelminar is.  If nothing is there, he is the most powerful.
	//			-- affected are the hit points and the shot damage.
	//	The hit points are controlled here, the shot damage is controlled
	// 	within the spawning of the shot.  See ShootPlayer for more info.
	//
	Grel_Hard = *(mapsegs[2]+farmapylookup[tiley+1]+tilex);
	if (Grel_Hard)
	{
		new->temp2 = Grel_Hard>>8;
		new->hitpoints = EasyHitPoints((new->temp2 * 10));
	}
	else
		new->hitpoints = EasyHitPoints(100);
}


/*
===============
=
= T_Grelminar
=
===============
*/

void T_Grelminar (objtype *ob)
{
	Chase (ob,false);

	if (!random(10))
		if (ShootPlayer(ob,gshotobj,ob->temp2,&s_gshot1))
		{
			ob->state = &s_grelattack3;
			ob->ticcount = ob->state->tictime;
		}
	if (CheckHandAttack(ob))
		TakeDamage (ob->temp2*3);

}


//=================================
//
// T_Grelm_DropKey
//
//=================================
void T_Grelm_DropKey(objtype *ob)
{
	if (!(ob->temp1))
	{
		ob->state = NULL;
		return;
	}

	SpawnBonus(ob->tilex,ob->tiley,B_RKEY);
	SD_PlaySound(GRELM_DEADSND);
	ob->temp1 = false;
}

/*
=============================================================================

							BAT

=============================================================================
*/

void T_Bat (objtype *ob);
void T_BatPast (objtype *ob);

extern	statetype s_bat1;
extern	statetype s_bat2;
extern	statetype s_bat3;
extern	statetype s_bat4;

extern	statetype s_batdie1;
extern	statetype s_batdie2;


statetype s_bat1 = {BAT1PIC,6,T_Bat,&s_bat2};
statetype s_bat2 = {BAT2PIC,6,T_Bat,&s_bat3};
statetype s_bat3 = {BAT3PIC,6,T_Bat,&s_bat4};
statetype s_bat4 = {BAT4PIC,6,T_Bat,&s_bat1};

statetype s_batpast = {BAT4PIC,80,T_BatPast,&s_bat1};

statetype s_batdie1 = {BATDIE1PIC,18,NULL,&s_batdie2};
statetype s_batdie2 = {BATDIE2PIC,18,NULL,NULL};


/*
===============
=
= SpawnBat
=
===============
*/

void SpawnBat (int tilex, int tiley)
{
	SpawnNewObj(tilex,tiley,&s_bat1,PIXRADIUS*35);
	new->obclass = batobj;
	new->flags |= of_shootable;

	new->hitpoints = 1;
	new->speed = 2000;
}


/*
==================================
=
= BatChaseThink
=
==================================
*/

void BatChaseThink (objtype *obj)
{
	int deltax,deltay;

	deltax=player->tilex - obj->tilex;
	deltay=player->tiley - obj->tiley;

	if (deltax>0)
		deltax = 2;
	else if (deltax<0)
		deltax = 0;
	else deltax = 1;

	if (deltay>0)
		deltay = 2;
	else if (deltay<0)
		deltay = 0;
	else deltay = 1;

	obj->dir = dirtable[deltay*3+deltax];
	if (Walk(obj))
		return;

	obj->dir = dirtable[3+deltax];
	if (Walk(obj))
		return;

	obj->dir = dirtable[deltay*3+1];
	if (Walk(obj))
		return;

	obj->dir = nodir;
}


void BatRunThink (objtype *obj)
{
	int deltax,deltay;

	deltax=player->tilex - obj->tilex;
	deltay=player->tiley - obj->tiley;

	if (deltax>=0)
		deltax = 0;
	else
		deltax = 2;

	if (deltay>=0)
		deltay = 0;
	else
		deltay = 2;

	obj->dir = dirtable[deltay*3+deltax];
	if (Walk(obj))
		return;

	obj->dir = dirtable[3+deltax];
	if (Walk(obj))
		return;

	obj->dir = dirtable[deltay*3+1];
	Walk(obj);
}



/*
===============
=
= T_Bat
=
===============
*/

void T_Bat (objtype *ob)
{
	long move;
	long deltax,deltay,size;

	move = ob->speed*tics;
	size = (long)ob->size + player->size + move;


	do
	{
		deltax = ob->x - player->x;
		deltay = ob->y - player->y;

		if (deltax <= size && deltax >= -size
		&& deltay <= size && deltay >= -size && !ob->temp1)
		{
			TakeDamage (4);
			ob->temp1 = 2;
		}

		if (move < ob->distance)
		{
			MoveObj (ob,move);
			break;
		}

		actorat[ob->tilex][ob->tiley] = 0;	// pick up marker from goal
		if (ob->dir == nodir)
			ob->dir = north;

		ob->x = ((long)ob->tilex<<TILESHIFT)+TILEGLOBAL/2;
		ob->y = ((long)ob->tiley<<TILESHIFT)+TILEGLOBAL/2;
		move -= ob->distance;

		if (ob->temp1)
		{
			Walk (ob);				// go straight
			if (!--ob->temp1)
			{
				ob->state = &s_batpast;
				ob->ticcount = ob->state->tictime;
			}
		}
		else
			BatChaseThink (ob);		// head towards player

		actorat[ob->tilex][ob->tiley] = ob;	// set down a new goal marker
	} while (0);	// just once
	CalcBounds (ob);
}


/*
===============
=
= T_BatPast
=
===============
*/

void T_BatPast (objtype *ob)
{
	long move;
	long deltax,deltay,size;

	move = ob->speed*tics;

	do
	{
		if (move < ob->distance)
		{
			MoveObj (ob,move);
			break;
		}
		actorat[ob->tilex][ob->tiley] = 0;	// pick up marker from goal

		ob->x = ((long)ob->tilex<<TILESHIFT)+TILEGLOBAL/2;
		ob->y = ((long)ob->tiley<<TILESHIFT)+TILEGLOBAL/2;
		move -= ob->distance;

		BatRunThink (ob);

		actorat[ob->tilex][ob->tiley] = ob;	// set down a new goal marker
	} while (0);	//(move)
	CalcBounds (ob);
}


void T_ChaseThink(objtype *obj);
void T_AwakeThink(objtype *obj);



/*
=============================================================================

							GODESS

=============================================================================
*/

void T_Godess (objtype *ob);


extern	statetype s_godesspause;

extern	statetype s_godess_statue1;
extern	statetype s_godess_statue2;

extern	statetype s_godess1;
extern	statetype s_godess2;
extern	statetype s_godess3;

extern	statetype s_godessattack1;
extern	statetype s_godessattack2;
extern	statetype s_godessattack3;

extern	statetype s_godessouch;

extern	statetype s_godessdie1;
extern	statetype s_godessdie2;
extern	statetype s_godessdie3;


statetype s_godesspause = {GODESS_WALK1PIC,25,NULL,&s_godess2};

statetype s_godess_statue1 = {GODESS_STATUEPIC,20,T_ChaseThink,&s_godess_statue1};
statetype s_godess_statue2 = {GODESS_STATUEPIC,1,T_AwakeThink,&s_godess1};

statetype s_godess1 = {GODESS_WALK1PIC,20,T_ChaseThink,&s_godess2};
statetype s_godess2 = {GODESS_WALK2PIC,20,T_ChaseThink,&s_godess3};
statetype s_godess3 = {GODESS_WALK3PIC,20,T_ChaseThink,&s_godess1};

statetype s_godessattack1 = {GODESS_ATTACK1PIC,10,NULL,&s_godessattack2};//20
statetype s_godessattack2 = {GODESS_ATTACK2PIC,8,NULL,&s_godessattack3};//20
statetype s_godessattack3 = {GODESS_ATTACK3PIC,10,T_DoDamage,&s_godesspause};//30

statetype s_godessouch = {GODESS_OUCHPIC,10,NULL,&s_godess1};

statetype s_godessdie1 = {GODESS_DEATH1PIC,65,NULL,&s_godessdie2};
statetype s_godessdie2 = {GODESS_DEATH2PIC,30,NULL,&s_godessdie2};



/*
===============
=
= SpawnGodess
=
===============
*/

void SpawnGodess (int tilex, int tiley)
{
	objtype *ob;
	short current_zombie_delay;
	unsigned tile;

	SpawnNewObj(tilex,tiley,&s_godess_statue1,PIXRADIUS*35);
	ob = new;
	zombie_mode = zm_wait_for_dark;

	tile = *(mapsegs[2]+farmapylookup[tiley+1]+tilex);
	if (tile)
		zombie_delay = (tile>>8)*30;
	else
	{
		current_zombie_delay = (2*60)+random(4*60);
		zombie_delay = zombie_base_delay+current_zombie_delay;
		zombie_base_delay += current_zombie_delay;
		if (zombie_base_delay > 8*60)
			zombie_base_delay = 0;
	}

	new->obclass = realsolidobj;//godessobj;
	new->speed = 3000;
	new->flags |= of_shootable;
	new->flags &= ~of_tree;
//	new->hitpoints = EasyHitPoints(10);
}




/*
=============================================================================

					ANT

=============================================================================
*/

void T_Ant(objtype *ob);

statetype s_ant_wait = {ANT_EGG1PIC,10,T_ChaseThink,&s_ant_wait};

statetype s_ant_egg = {ANT_EGG2PIC,45,T_AwakeThink,&s_ant_walk1};

statetype s_ant_walk1 = {ANT_WALK1PIC,20,T_ChaseThink,&s_ant_walk2};
statetype s_ant_walk2 = {ANT_WALK2PIC,20,T_ChaseThink,&s_ant_walk3};
statetype s_ant_walk3 = {ANT_WALK3PIC,20,T_ChaseThink,&s_ant_walk1};

statetype s_ant_attack1 = {ANT_ATTACKPIC,20,NULL,&s_ant_pause};

statetype s_ant_pause  = {ANT_WALK2PIC,15,T_DoDamage,&s_ant_walk1};

statetype s_ant_ouch = {ANT_WALK1PIC,15,NULL,&s_ant_walk1};

statetype s_ant_die1 = {ANT_DEATH1PIC,40,NULL,&s_ant_die2};
statetype s_ant_die2 = {ANT_DEATH2PIC,10,NULL,&s_ant_die3};
statetype s_ant_die3 = {ANT_DEATH3PIC,10,NULL,&s_ant_die2};

#define ant_mode	ob->temp1
#define ant_delay	ob->temp2

/*
===============
=
= SpawnAnt
=
===============
*/
void SpawnAnt(int tilex, int tiley)
{
	objtype *ob;
	unsigned tile;
	SpawnNewObj(tilex,tiley,&s_ant_wait,PIXRADIUS*35);
	ob = new;

	tile = *(mapsegs[2]+farmapylookup[tiley+1]+tilex);
	if (tile)
		ant_delay = (tile>>8)*30;
	else
		ant_delay = 2*60+random(5*60);

	ant_mode = zm_wait_for_dark;

	new->obclass = antobj;
	new->speed = 1900;
	new->flags &= ~of_shootable;
	new->hitpoints = EasyHitPoints(15);
}



/*
=============================================================================

							ZOMBIE

=============================================================================
*/

extern statetype s_zombie_rise1;
extern statetype s_zombie_rise2;
extern statetype s_zombie_rise3;
extern statetype s_zombie_rise4;

extern statetype s_zombie_alive1;
extern statetype s_zombie_alive2;
extern statetype s_zombie_alive3;

//extern statetype s_zombie_attack1;

extern statetype s_zombie_death1;
extern statetype s_zombie_death2;
extern statetype s_zombie_death3;

void T_Zombie (objtype *ob);
void T_ZombieRisen(objtype *obj);

statetype s_zombie_risen = {ZOMB_WALK3PIC,1,T_AwakeThink,&s_zombie_alive1};

statetype s_zombie_pause = {ZOMB_WALK1PIC,20,NULL,&s_zombie_alive1};

statetype s_zombie_inground = {0,13,T_ChaseThink,&s_zombie_inground};

statetype s_zombie_rise1 = {ZOMB_APPEAR1PIC,24,NULL,&s_zombie_rise2};
statetype s_zombie_rise2 = {ZOMB_APPEAR2PIC,24,NULL,&s_zombie_rise3};
statetype s_zombie_rise3 = {ZOMB_APPEAR3PIC,24,NULL,&s_zombie_rise4};
statetype s_zombie_rise4 = {ZOMB_APPEAR4PIC,24,NULL,&s_zombie_risen};

statetype s_zombie_alive1 = {ZOMB_WALK1PIC,13,T_ChaseThink,&s_zombie_alive2};
statetype s_zombie_alive2 = {ZOMB_WALK2PIC,13,T_ChaseThink,&s_zombie_alive3};
statetype s_zombie_alive3 = {ZOMB_WALK3PIC,13,T_ChaseThink,&s_zombie_alive1};

statetype s_zombie_death1 = {ZOMB_DIE1PIC,16,NULL,&s_zombie_death2};
statetype s_zombie_death2 = {ZOMB_DIE2PIC,16,NULL,&s_zombie_death3};
statetype s_zombie_death3 = {ZOMB_DIE3PIC,16,NULL,&s_zombie_death3};

statetype s_zombie_attack  = {ZOMB_ATTACKPIC,15,T_DoDamage,&s_zombie_pause};
//statetype s_zombie_attack1 = {ZOMB_ATTACKPIC,15,NULL,&s_zombie_pause};

statetype s_zombie_ouch = {ZOMB_OUCHPIC,15,NULL,&s_zombie_alive1};


//--------------------------------------------------------------------------
// SpawnZombie()
//--------------------------------------------------------------------------
void SpawnZombie (int tilex, int tiley)
{
	objtype *ob;
	short current_zombie_delay;
	unsigned tile;

	SpawnNewObj(tilex,tiley,&s_zombie_inground,35*PIXRADIUS);
	ob = new;
	zombie_mode = zm_wait_for_dark;

	tile = *(mapsegs[2]+farmapylookup[tiley+1]+tilex);
	if (tile)
		zombie_delay = (tile>>8)*30;
	else
	{
		current_zombie_delay = (2*60)+random(4*60);
		zombie_delay = zombie_base_delay+current_zombie_delay;
		zombie_base_delay += current_zombie_delay;
		if (zombie_base_delay > 8*60)
			zombie_base_delay = 0;
	}

	new->speed = 2500;
	new->obclass = zombieobj;
	new->hitpoints = EasyHitPoints(8);
	new->active = yes;
	new->flags &= ~of_shootable;
}


/*
=============================================================================

					TREE

=============================================================================
*/

extern statetype s_tree_pause;
extern statetype s_tree_idle;
extern statetype s_tree_awakening1;
extern statetype s_tree_awakening2;
extern statetype s_tree_walk1;
extern statetype s_tree_walk2;
extern statetype s_tree_walk3;
extern statetype s_tree_death1;
extern statetype s_tree_death2;
extern statetype s_tree_death3;
extern statetype s_tree_death4;
extern statetype s_tree_death5;
extern statetype s_tree_attack1;
extern statetype s_tree_attack2;
extern statetype s_tree_attack3;
extern statetype s_tree_ouch;

void T_Tree (objtype *ob);
void T_DeathThink(objtype *ob);

statetype s_tree_pause = {TREE_WALK1PIC,25,NULL,&s_tree_walk2};

statetype s_tree_idle = {TREE_IDLEPIC,13,T_ChaseThink,&s_tree_idle};

statetype s_tree_awakening1 = {TREE_AWAKENINGPIC,1,T_AwakeThink,&s_tree_awakening2};
statetype s_tree_awakening2 = {TREE_AWAKENINGPIC,50,NULL,&s_tree_walk1};

statetype s_tree_walk1 = {TREE_WALK1PIC,13,T_ChaseThink,&s_tree_walk2};
statetype s_tree_walk2 = {TREE_WALK2PIC,13,T_ChaseThink,&s_tree_walk1};

statetype s_tree_death1 = {TREE_DEATH1PIC,45,NULL,&s_tree_death2};
statetype s_tree_death2 = {TREE_DEATH2PIC,25,NULL,&s_tree_death3};
statetype s_tree_death3 = {TREE_DEATH1PIC,15,T_DeathThink,&s_tree_death4};
statetype s_tree_death4 = {TREE_DEATH2PIC,15,T_DeathThink,&s_tree_death5};
statetype s_tree_death5 = {TREE_DEATH3PIC,15,T_DeathThink,&s_tree_death3};

statetype s_tree_attack1  = {TREE_ATTACK1PIC,15,T_DoDamage,&s_tree_attack2};
statetype s_tree_attack2  = {TREE_ATTACK2PIC,15,T_DoDamage,&s_tree_attack3};
statetype s_tree_attack3  = {TREE_ATTACK3PIC,15,T_DoDamage,&s_tree_pause};

statetype s_tree_ouch = {TREE_AWAKENINGPIC,15,NULL,&s_tree_walk1};


#define zombie_mode	ob->temp1
#define zombie_delay	ob->temp2


//--------------------------------------------------------------------------
// SpawnTree()
//--------------------------------------------------------------------------
void SpawnTree(int tilex, int tiley)
{
	objtype *ob;
	short current_zombie_delay;
	unsigned tile;

	SpawnNewObj(tilex,tiley,&s_tree_idle,35*PIXRADIUS);
	ob = new;
	zombie_mode = zm_wait_for_dark;

	tile = *(mapsegs[2]+farmapylookup[tiley+1]+tilex);
	if (tile)
		zombie_delay = (tile>>8)*30;
	else
	{
		current_zombie_delay = (2*60)+random(4*60);
		zombie_delay = zombie_base_delay+current_zombie_delay;
		zombie_base_delay += current_zombie_delay;
		if (zombie_base_delay > 8*60)
			zombie_base_delay = 0;
	}

	new->speed = 2500;
	new->obclass = realsolidobj;
//	new->hitpoints = EasyHitPoints(12);
	new->active = yes;
	new->flags |= of_shootable;
	new->flags |= of_tree;
}

//--------------------------------------------------------------------------
// T_DeathThink()
//--------------------------------------------------------------------------
void T_DeathThink(objtype *ob)
{
	char num;

	if ((ob->ticcount - realtics) <= 0)
	{
		num = random(2);
		switch (ob->temp1)
		{
			case 3:
				if (num)
					ob->state = &s_tree_death4;
				else
					ob->state = &s_tree_death5;
				ob->temp1++;
			break;

			case 4:
				if (num)
					ob->state = &s_tree_death3;
				else
					ob->state = &s_tree_death5;
				ob->temp1++;
			break;

			case 5:
				if (num)
					ob->state = &s_tree_death3;
				else
					ob->state = &s_tree_death4;
				ob->temp1 = 3;
			break;
		}
		ob->ticcount = ob->state->tictime;
	}



	if (CheckHandAttack(ob))
		TakeDamage (1);
}


//////////////////////////////////////////////////////////////////////////
//
//     GENERAL THINK ROUTINES USED BY THE ZOMBIE, TREE, ANT, AND GODESS
//             ----trying to cut down on the code size----
//
//////////////////////////////////////////////////////////////////////////


//--------------------------------------------------------------------------
// T_ChaseThink()
//--------------------------------------------------------------------------
void T_ChaseThink(objtype *ob)
{
	switch (zombie_mode)
	{
		case zm_wait_for_dark:
#if 0
			if (gamestate.mapon == 0)
			{
				if (BGFLAGS & BGF_NIGHT)
					zombie_mode = zm_wait_to_rise;
			}
			else
#endif
				zombie_mode = zm_wait_to_rise;
		break;

		case zm_wait_to_rise:
			if (zombie_delay < 0)
			{
				if ((ob->tilex == player->tilex) && (ob->tiley == player->tiley))
					break;
				if (CheckHandAttack(ob))
					break;

				ob->active = always;
				switch (ob->obclass)
				{
					case zombieobj:
						ob->state = &s_zombie_rise1;
					break;

					case antobj:
						ob->state = &s_ant_egg;
					break;

					case realsolidobj:	//tree and godess
						if (ob->flags & of_tree)
							ob->state = &s_tree_awakening1;
						else
							ob->state = &s_godess_statue2;
					break;
				}
				ob->ticcount = ob->state->tictime;
				zombie_mode = zm_active;
			}
			else
				zombie_delay -= tics;

		break;

		case zm_active:
			if (Chase (ob,true) || (random(1000)<RANDOM_ATTACK))
			{
				switch (ob->obclass)
				{
					case zombieobj:
						ob->state = &s_zombie_attack;
					break;

					case antobj:
						ob->state = &s_ant_attack1;
					break;

					case treeobj:
						ob->state = &s_tree_attack1;
					break;

					case godessobj:
						ob->state = &s_godessattack1;
					break;
				}
				ob->ticcount = ob->state->tictime;
				return;
			}
		break;
	}
}

//--------------------------------------------------------------------------
// T_AwakeThink()
//--------------------------------------------------------------------------
void T_AwakeThink(objtype *obj)
{
	if (obj->obclass == realsolidobj)
	{
		if (obj->flags & of_tree)
			obj->obclass = treeobj;
		else
			obj->obclass = godessobj;
		obj->hitpoints = EasyHitPoints(12);
	}
	else
		obj->flags |= of_shootable;
}





//--------------------------------------------------------------------------
// ShootPlayer()
//--------------------------------------------------------------------------
boolean ShootPlayer(objtype *ob, short obclass, short speed, statetype *state)
{
	int angle = AngleNearPlayer(ob);

	if (angle == -1)
		return(false);

	DSpawnNewObjFrac (ob->x,ob->y,state,PIXRADIUS*35);
	new->obclass = obclass;
	new->active = always;
	new->angle = angle;

	//
	//	If the shot is Grelminar's, then determine the power of the shot.
	//	The shot speed is hard-wired as 10000.  But the shot power is
	//		determined by speed.  Speed now contains "Grelminar's level of
	//		hardness" and this is multiplied by 3 to get the shot power.
	//
	if (obclass == gshotobj)
	{
		new->speed = 10000;
		new->temp1 = speed*3;
	}
	else
		new->speed = speed;


	return(true);
}

//--------------------------------------------------------------------------
// T_ShootPlayer()
//--------------------------------------------------------------------------
void T_ShootPlayer(objtype *ob)
{
	objtype *check;
	long xmove,ymove,speed;

	speed = ob->speed*tics;

	xmove = FixedByFrac(speed,costable[ob->angle]);
	ymove = -FixedByFrac(speed,sintable[ob->angle]);

	if (ShotClipMove(ob,xmove,ymove))
	{
		ob->state = &s_pshot_exp1;
		ob->ticcount = ob->state->tictime;
		return;
	}

	ob->tilex = ob->x >> TILESHIFT;
	ob->tiley = ob->y >> TILESHIFT;


// check for collision with wall
//
	if (tilemap[ob->tilex][ob->tiley])
	{
		SD_PlaySound (SHOOTWALLSND);
		ob->state = &s_pshot_exp1;
		ob->ticcount = s_pshot_exp1.tictime;
		return;
	}



// check for collision with player
//
	if ( ob->xl <= player->xh
	&& ob->xh >= player->xl
	&& ob->yl <= player->yh
	&& ob->yh >= player->yl)
	{
		switch (ob->obclass)
		{
			case eshotobj:
				TakeDamage (ESHOTDAMAGE);
			break;

			case mshotobj:
				TakeDamage (MSHOTDAMAGE);
			break;

			case gshotobj:
				TakeDamage (ob->temp1);		// the damage of Grelminar's shot -
			break;								//   see Grelminar's spawning

			case sshotobj:
				TakeDamage(SSHOTDAMAGE);
			break;

			case dshotobj:
				TakeDamage(7);
			break;
		}
		ob->state = NULL;
		return;
	}

// check for collision with other solid and realsolid objects.
//  Great terminology!! -- solid objects really aren't solid
//                      -- realsolid objects ARE solid
//	if ((actorat[ob->tilex][ob->tiley]) && (actorat[ob->tilex][ob->tiley]->obclass != ob->obclass))
	if (((actorat[ob->tilex][ob->tiley]->obclass == realsolidobj) ||
		 (actorat[ob->tilex][ob->tiley]->obclass == solidobj)) &&
		 (actorat[ob->tilex][ob->tiley]->flags & of_shootable))
	{
			ob->state = &s_pshot_exp1;
			ob->ticcount = s_pshot_exp1.tictime;
			return;
	}


// check for collision with player
//
	for (check = player->next; check; check=check->next)
		if ((ob->flags & of_shootable) && ob->obclass != mageobj
		&& ob->xl <= check->xh
		&& ob->xh >= check->xl
		&& ob->yl <= check->yh
		&& ob->yh >= check->yl)
		{
			switch (ob->obclass)
			{
				case eshotobj:
					ShootActor (check,ESHOTDAMAGE);
				break;

				case mshotobj:
					ShootActor (check,MSHOTDAMAGE);
				break;

				case gshotobj:
					ShootActor (check,25);		//NOLAN--check on me!!!!!!!
				break;

				case pshotobj:
					ShootActor (check,25);
				break;

				case sshotobj:
					ShootActor(check, SSHOTDAMAGE);
				break;

				case dshotobj:
					ShootActor(check, 7);
				break;
			}
			ob->state = &s_pshot_exp1;
			ob->ticcount = s_pshot_exp1.tictime;
			return;
		}
}

//-------------------------------------------------------------------------
// AngleNearPlayer()
//-------------------------------------------------------------------------
int AngleNearPlayer(objtype *ob)
{
	int angle=-1;
	int xdiff = ob->tilex-player->tilex;
	int ydiff = ob->tiley-player->tiley;

	if (ob->tiley == player->tiley)
	{
		if (ob->tilex < player->tilex)
			angle = 0;
		else
			angle = 180;
	}
	else
	if (ob->tilex == player->tilex)
	{
		if (ob->tiley < player->tiley)
			angle = 270;
		else
			angle = 90;
	}
	else
	if (xdiff == ydiff)
		if (ob->tilex < player->tilex)
		{
			if (ob->tiley < player->tiley)
				angle = 315;
			else
				angle = 45;
		}
		else
		{
			if (ob->tiley < player->tiley)
				angle = 225;
			else
				angle = 135;
		}

	return(angle);
}
