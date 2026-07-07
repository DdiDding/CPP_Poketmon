#include "Skill.h"
#include <iostream>

using namespace std;

string  Skill::get_name() { return this->_name; };
bool Skill::get_is_attack() { return this->_is_attack; };
int  Skill::get_damage() { return this->_damage; };
int  Skill::get_atk_type() { return this->_atk_type; };
int  Skill::get_type() { return this->_type;; };
int  Skill::get_hit_num() { return this->_hit_num; };
int  Skill::get_is_strange() { return this->_is_strange; };
int  Skill::get_strange_num() { return this->_strange_num; };
int  Skill::get_strange_type() { return this->_strange_type; };
int  Skill::get_what_my_stat() { return this->_what_my_stat; };
int  Skill::get_what_your_stat() { return this->_what_your_stat; };
int  Skill::get_heal() { return this->_heal; }


void Skill::set_name(string _name) { this->_name = _name; };
void Skill::set_damage(int _damage) { this->_damage = _damage; };
void Skill::set_atk_type(int _atk_type) { this->_atk_type = _atk_type; };
void Skill::set_type(int _type) { this->_type = _type; };
void Skill::set_hit_num(int _hit_num) { this->_hit_num = _hit_num; };
void Skill::set_is_strange(bool _is_strange) { this->_is_strange = _is_strange; };
void Skill::set_strange_num(int _strange_num) { this->_strange_num = _strange_num; };
void Skill::set_strange_type(int _strange_type) { this->_strange_type = _strange_type; };
void Skill::set_what_my_stat(int _what_my_stat) { this->_what_my_stat = _what_my_stat; };
void Skill::set_what_your_stat(int _what_your_stat) { this->_what_your_stat = _what_your_stat; };
void Skill::set_heal(int _heal) { this->_heal = _heal; };
