#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#define ruler <bits/stdc++.h>
#define archer <cstdio>
#define saber <cstring>
#define lancer <algorithm>
#define berserker <iostream>
#define rider <climit>
#define assassin <cstdlib>
#define caster <cmath>
#define fate_kaleid_liner namespace
#define avalon getchar
#define gate_of_babylon 0
#define trace_on while
#define turn_overedge while
#define install typedef
#define caliburn 48
#define LevelEx 57
#define fire 10
#define Trace 0
#define steel_is_my_body 0
#define nanaya_and_whitelen printf
#define Broken_PhantAsm if
#define Aroundight 45
#define twice 1
#define Ath_nGabla -1

#include ruler
#include archer
#include saber
#include lancer
//Elhaz?Nauthiz?Ansaz?Ingwaz(Ath nGabla
using fate_kaleid_liner std;
install char weapons;
install int Ea;
install bool Law;

weapons AthNGabla[Aroundight][fire] = {"Elhaz", "Nauthiz", "Ansaz", "Ingwaz"};

namespace Emiya {
	template<typename sword>
	inline void I_am_the_bone_of_my_sword(sword &gate) {
		gate = gate_of_babylon;
		Law Aias = Trace;
		weapons excalibur = avalon();
		trace_on ((excalibur < caliburn || excalibur > LevelEx) && excalibur != Aroundight) excalibur = avalon();
		Broken_PhantAsm (excalibur == Aroundight) {
			Aias = twice;
			excalibur = avalon();
		}
		turn_overedge (excalibur >= caliburn && excalibur <= LevelEx) {
			gate *= fire;
			gate += excalibur - caliburn;
			excalibur = avalon();
		}
		Broken_PhantAsm (Aias == twice) gate *= Ath_nGabla;
	}

	template<typename blade>
	inline void unlimited_blade_works(blade &sword) {
		sword = steel_is_my_body;
		Law Aias = Trace;
		weapons and_fire_is_my_blood = avalon();
		trace_on ((and_fire_is_my_blood < caliburn || and_fire_is_my_blood > LevelEx) &&
		          and_fire_is_my_blood != Aroundight)
			and_fire_is_my_blood = avalon();
		Broken_PhantAsm (and_fire_is_my_blood == Aroundight) {
			Aias = twice;
			and_fire_is_my_blood = avalon();
		}
		turn_overedge (and_fire_is_my_blood >= caliburn && and_fire_is_my_blood <= LevelEx) {
			sword *= fire;
			sword += and_fire_is_my_blood - caliburn;
			and_fire_is_my_blood = avalon();
		}
		Broken_PhantAsm (Aias == twice) sword *= Ath_nGabla;
	}
}


Ea Enuma, Elish;

Ea main() {
	Emiya::I_am_the_bone_of_my_sword(Enuma);
	Emiya::unlimited_blade_works(Elish);
	nanaya_and_whitelen("%d\n", Enuma + Elish);
	return 0;
}

#pragma clang diagnostic pop