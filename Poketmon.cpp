#include "Poketmon.h"
#include <iostream>


string Poketmon::get_name()         {return this->_name      ;}; 
int Poketmon::get_type() { return this->_type; };
int Poketmon::get_atk()		  {return this->_atk		;};
int Poketmon::get_def()		  {return this->_def		;};
int Poketmon::get_s_atk()		  {return this->_s_atk		;};
int Poketmon::get_s_def()		  {return this->_s_def		;};
int Poketmon::get_fast()		  {return this->_fast		;};
int Poketmon::get_avd()		  {return this->_avd		;};
int Poketmon::get_hp()			  {return this->_hp	;};	
int Poketmon::get_temp_hp()	  {return this->_temp_hp	;};
int Poketmon::get_rank_atk()	  {return this->_rank_atk	;};
int Poketmon::get_rank_def()	  {return this->_rank_def	;};
int Poketmon::get_rank_s_atk()	  {return this->_rank_s_atk;};	
int Poketmon::get_rank_s_def()	  {return this->_rank_s_def;};	
int Poketmon::get_rank_fast()	  {return this->_rank_fast	;};
int Poketmon::get_rank_avd()	  {return this->_rank_avd	;};
int Poketmon::get_status()		  {return this->_status	;};	
int Poketmon::get_confusion()	  {return this->_confusion	;};
int Poketmon::get_lv() {return this->_lv = _lv; };
int Poketmon::get_exp() {return this->_exp = _exp; };
bool Poketmon::get_evolution() {return this->_evolution = _evolution; };
Skill (* Poketmon::get_skill())[4]		  {return this->_skill		;}
bool Poketmon::get_can_atk() { return this->_can_atk; };
bool Poketmon::get_join_battle() { return this->_join_battle; };


void Poketmon::set_name(string _name)			{this->_name = _name            ;};     
void Poketmon::set_type(int _type) { this->_type = _type; };
void Poketmon::set_atk(int _atk)				{this->_atk =_atk				;};
void Poketmon::set_def(int _def)				{this->_def =_def				;};
void Poketmon::set_s_atk(int _s_atk)			{this->_s_atk =_s_atk			;};
void Poketmon::set_s_def(int _s_def)			{this->_s_def =_s_def			;};
void Poketmon::set_fast(int _fast)				{this->_fast =_fast				;};
void Poketmon::set_avd(int _avd)				{this->_avd	=_avd				;};
void Poketmon::set_hp(int _hp)					{this->_hp = _hp				;};
void Poketmon::set_temp_hp(int _temp_hp)		{this->_temp_hp	=_temp_hp		;};
void Poketmon::set_rank_atk(int _rank_atk)		{this->_rank_atk =_rank_atk		;};
void Poketmon::set_rank_def(int _rank_def)		{this->_rank_def =_rank_def		;};
void Poketmon::set_rank_s_atk(int _rank_s_atk)	{this->_rank_s_atk = _rank_s_atk;};
void Poketmon::set_rank_s_def(int _rank_s_def)	{this->_rank_s_def = _rank_s_def;};
void Poketmon::set_rank_fast(int _rank_fast)	{this->_rank_fast =_rank_fast	;};
void Poketmon::set_rank_avd(int _rank_avd)		{this->_rank_avd =_rank_avd		;};
void Poketmon::set_status(int _status)			{this->_status = _status		;};
void Poketmon::set_confusion(int _confusion)	{this->_confusion =_confusion	;};
void Poketmon::set_lv(int _lv)				    {this->_lv = _lv;};
void Poketmon::set_exp(int _exp)				{this->_exp = _exp;};
void Poketmon::set_evolution(int _evolution)	{this->_evolution = _evolution;};
void Poketmon::set_skill(Skill(*_skill)[4])		{this->_skill =_skill			;};
void Poketmon::set_can_atk(bool _can_atk)		{this->_can_atk = _can_atk; };
void Poketmon::set_join_battle(bool _join_battle) { this->_join_battle = _join_battle; };



void Poketmon::Hp_sub(int damage){

	this->_temp_hp -= damage;
	if (this->_temp_hp < 0) _temp_hp = 0;
}
void Poketmon::Hp_plus(int heal){

	this->_temp_hp += heal;
	if (this->_temp_hp > this->_hp) _temp_hp = _hp;
}



int Poketmon::get_b_atk()
{
	return (this->_atk + (this->_rank_atk * 10));
}

int Poketmon::get_b_def()
{
	return (this->_def + (this->_rank_def * 10));
}

int Poketmon::get_b_s_atk()
{
	return (this->_s_atk + (this->_rank_s_atk * 10));
}

int Poketmon::get_b_s_def()
{
	return (this->_s_def + (this->_rank_s_def * 10));
}

int Poketmon::get_b_fast()
{
	return (this->_fast + (this->_rank_fast * 10));
}

int Poketmon::get_b_avd()
{
	return (this->_avd + (this->_rank_avd * 10));
}

void Poketmon::Lv_up()
{
		this->_lv++;
		this->_atk += 50;
		this->_s_atk += 50;
		this->_def += 50;
		this->_s_def += 50;
		this->_fast += 50;
		this->_avd += 50;
}

void Poketmon::Evolution_stat()
{
	this->_atk += 150;
	this->_s_atk += 150;
	this->_def += 150;
	this->_s_def += 150;
	this->_fast += 150;
	this->_avd += 150;
	this->_hp += 150;
	this->_temp_hp += 150;
}

//true면 레벨업, false면 아님
bool Poketmon::Exp_plus(int exp)
{
	this->_exp += exp;
	if (this->_exp >= 100) {
		return true;
	}
	return false;
}

void Poketmon::confuse_damage() {

	Hp_sub(40);
}