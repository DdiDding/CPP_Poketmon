#pragma once
#include <string>

struct Item
{
	Item(string name, int index, int many,string info) {
		this->_name = name;
		this->_index = index;
		this->_many = many;
		this->_info = info;
	}

	int _index;
	int _many;
	string _name;
	string _info;
};

Item hyper_heal("하이퍼 회복약",0, 1,"HP를 500 회복합니다");
Item rebirth("기력의 조각",1, 3,"빈사상태의 포켓몬을 절반의 Hp로 부활시킵니다");
Item release_poison("해독제",2, 15,"독 상태에서 벗어납니다");
Item release_electric("마비 치료제",3, 15,"마비 상태에서 벗어납니다");
Item speed_up("스피드 업",4, 20,"선택한 포켓몬의 스피드를 1랭크 상승시킵니다");

