#pragma once
#include <iostream>

using namespace std;

//스킬 여러개가아닌 하나하나의 단독적 스킬 클래스
class Skill
{
public:
	
	/*
	1.string 이름
	2.bool 공격 하는지 안하는지 체크 true면 공격 , false면 변화만
	3.int 데미지 [ hp비례면 퍼센트로 생각하자]
	4.int 무슨 공격임 //공격 속성, 0 - 물리  1 - 특수   2 - 변화물리   3- 변화특수   4-hp비례  5- only변화
	5.int 속성뭐임
	6.int 명중률 몇퍼임
	7.bool 상태이상 걸리게함?  //false - 없음 , true - 있음
	8.int 상태이상 걸리게할 확률
	9.int 무슨 상태이상임   0 - 없음
							1 - 독
							2 - 마비
							3 - 얼음
							4 - 화상
							5 - 혼란
							6 - 내가잠듦
							7 - 상대가 잠듦 인데 기술이 없넹 ㅋㅋ

	10.int혹시 내 스텟 올림?    //0 - 없음 (넘어가기)
	11.int혹시 상대 스텟 올림??//1 - atk		양수면 랭크상승 음수면 랭크하락
							//2 - s_atk
							//3 - def
							//4 - s_def
							//5 - fast
							//6 - avd
	12.int혹시 회복함??  // 체력회복 양 ,
						is_atk 이 true면 데미지를 기반 비례 50은 50% 하고 100은 +상태회복까지 , 기가드레인
						false면 자기 전체체력에 비례 // 잠자기, hp회복
	*/
	Skill(string _name, bool _is_attack, int _damage, int _atk_type, int _type, int _hit_num, bool _is_strange, int _strange_num, int _strange_type, int _what_my_stat, int _what_your_stat, int _heal) {
		this->_name = _name;
		this->_is_attack = _is_attack;
		this->_damage = _damage;
		this->_atk_type = _atk_type;
		this->_type = _type;
		this->_hit_num = _hit_num;
		this->_is_strange = _is_strange;
		this->_strange_num = _strange_num;
		this->_strange_type = _strange_type;
		this->_what_my_stat = _what_my_stat;
		this->_what_your_stat = _what_your_stat;
		this->_heal = _heal;
	}



	string  get_name();
	bool get_is_attack();
	int  get_damage();
	int  get_atk_type();
	int  get_type();
	int get_hit_num();
	int  get_is_strange();
	int  get_strange_num();
	int  get_strange_type();
	int  get_what_my_stat();
	int  get_what_your_stat();
	int  get_heal();

	void set_name(string _name);
	void set_damage(int _damage);
	void set_atk_type(int _atk_type);
	void set_type(int _type);
	void set_hit_num(int _hit_num);
	void set_is_strange(bool _is_strange);
	void set_strange_num(int _strange_num);
	void set_strange_type(int _strange_type);
	void set_what_my_stat(int _what_my_stat);
	void set_what_your_stat(int _what_your_stat);
	void set_heal(int _heal);


private:
	string _name;

	bool _is_attack;//공격하는 스킬인지 아닌지
	
	int _damage; //위력

	int _atk_type; // 공격 속성, 0 - 물리  1 - 특수  2 - 변화물리 3- 변화특수 4-hp비례
	int _type; //공격 타입(풀,불,물...)
	int _hit_num; // 명중률

	bool _is_strange; // 특수효과가 있는지? false - 없음 , true - 있음  [상태이상 , 랭크변화 , 회복 을 말하는거임]

	
	int _strange_num; //상태이상 걸리게 할 확률
	int _strange_type; //어떤 상태이상을 주는가? 
						/*	0 - 없음
							1 - 독
							2 - 마비
							3 - 얼음
							4 - 화상
							5 - 혼란 */
	

	int _what_my_stat; //어떠한 능력치를 조절하는지 , //0 - 없음 (넘어가기)
	int _what_your_stat; //상대,				      //1 - atk		양수면 랭크상승 음수면 랭크하락
													  //2 - s_atk
													  //3 - def
													  //4 - s_def
													  //5 - fast
													  //6 - avd

	int _heal; // 체력회복 양 , -1,모두회복,상태이상 해제   0 - 없음 , 1 이상 데미지비례 퍼센트
};


