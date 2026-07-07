#pragma once
#include <iostream>
#include "Skill.h"

using namespace std;

class Poketmon
{
public:
	//이름,타입,공격,방어,특공,특방,속도,회피,체력,레벨,경험치,진화유무,스킬 [총 13개]
	Poketmon(string _name,int _type, int _atk, int _def, int _s_atk, int _s_def, int _fast, int _avd, int _hp, int _lv, int _exp, int _evolution, Skill(*_skill)[4]) {
		this->_name = _name;
		this->_type = _type;
		this->_atk = _atk;
		this->_def = _def;
		this->_s_atk = _s_atk;
		this->_s_def = _s_def;
		this->_fast = _fast;
		this->_avd = _avd;
		this->_hp = _hp;
		this->_temp_hp = _hp;
		this->_rank_atk = 0;
		this->_rank_def = 0;
		this->_rank_s_atk = 0;
		this->_rank_s_def =0;
		this->_rank_fast = 0;
		this->_rank_avd = 0;
		this->_status = 0;
		this->_confusion = 0;
		this->_lv = _lv;
		this->_exp = _exp;
		this->_evolution = _evolution;
		this->_skill =_skill;
		this->_can_atk = true;
		this->_join_battle = false;
	}


	void set_name			(string _name	  );
	void set_type			(int _type		  );
	void set_atk			(int _atk		  );
	void set_def			(int _def		  );
	void set_s_atk			(int _s_atk		  );
	void set_s_def			(int _s_def		  );
	void set_fast			(int _fast		  );
	void set_avd			(int _avd		  );
	void set_hp				(int _hp		  );
	void set_temp_hp		(int _temp_hp	  );
	void set_rank_atk		(int _rank_atk	  );
	void set_rank_def		(int _rank_def	  );
	void set_rank_s_atk		(int _rank_s_atk  );
	void set_rank_s_def		(int _rank_s_def  );
	void set_rank_fast		(int _rank_fast	  );
	void set_rank_avd		(int _rank_avd	  );
	void set_status			(int _status	  );
	void set_confusion		(int _confusion	  );
	void set_lv				(int _lv	  );
	void set_exp			(int _exp	  );
	void set_evolution		(int _evolution);
	void set_skill (Skill (*_skill)[4]);
	void set_can_atk(bool _can_atk);
	void set_join_battle(bool _join_battle);

	string get_name();
	int get_type();
	int get_atk();
	int get_def();
	int get_s_atk();
	int get_s_def();
	int get_fast();
	int get_avd();
	int get_hp();
	int get_temp_hp();
	int get_rank_atk();
	int get_rank_def();
	int get_rank_s_atk();
	int get_rank_s_def();
	int get_rank_fast();
	int get_rank_avd();
	int get_status();
	int get_confusion();
	int get_lv();
	int get_exp();
	bool get_evolution();
	Skill(*get_skill())[4];
	bool get_join_battle();

	//스텟과 랭크를 합해서 돌려주는 함수들
	int get_b_atk();
	int get_b_def();
	int get_b_s_atk();
	int get_b_s_def();
	int get_b_fast();
	int get_b_avd();
	bool get_can_atk();

	void Hp_sub(int damage);
	void Hp_plus(int heal);

	bool Exp_plus(int exp);

	void Lv_up();

	void Evolution_stat();

	void confuse_damage();


private:
	string _name;//포켓몬 이름

	int _type;//포켓몬 타입
	int _atk; //물리공격
	int _def; //물리방어
	int _s_atk; //특수공격
	int _s_def; //특수방어
	int _fast; //스피드
	int _avd; //회피율
	int _hp; //체력
	int _temp_hp; //계산용 체력

	//능력치 향상 기술사용시 맥스치 막기용
	int _rank_atk;
	int _rank_def;
	int _rank_s_atk;
	int _rank_s_def;
	int _rank_fast;
	int _rank_avd;


	int _status;/*상태이상
			   -1 - 빈사상태
				0 - 기본
				1 - 독	 [ 전체 체력 1/16 감소 ]
				2 - 마비 [ 25% 확률로 행동불가 , 스피드 절반(걸릴때 계산) ]
				3 - 화상 [ 체력 1/16 감소 , 물공 절반(걸릴때 계산) ]
				4 - 얼음 [ 20% 확률로 해제 ]
				5~ -잠듦 [ 기본 25,%해제 턴 올라갈때마다 25%증가 5에서 1씩 늘어남]
				*/
	int _confusion; //혼란상태 0 - 없음 , 1 이상 - 걸려있음 /해제 확률은 기본 25% , 매 턴마다 해제 확률 +25%

	int _lv; //레벨.. 개억지`~~~ㅋㅋㅋㅋㅋㅋㅋ
	int _exp; //경험치  Max 100으로 설정
	int _evolution; // false; 아직 진화 안함, true 진화 마침 ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ
	bool _can_atk; //공격가능한지 , 안가능한지
	bool _join_battle;//전투참여했는지 안했는지?
	Skill(*_skill)[4]; //스킬 4개
};
//잠들어 버렸다!
//마비되어 기술이 나오기 어려워졌다!
//몸이 저려서 움직일 수 없다!
//얼어버려서 움직일 수 없다!

//아이템 사용부분,

//공격해서 상애이상 걸때  x 3
