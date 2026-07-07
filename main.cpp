#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <vector>

#include "Skill.h"
#include "Type.h"
#include "List_pok.h"
#include "List_skill.h"
#include "Poketmon.h"
#include "Item.h"
#include "TItle.h"

#define BLUE 3
#define WHITE 7
#define RED 4
#define GRAY 8
#define YELLOW 14
#define GREAN 2
#define SKY 11
#define PURPLE 5
#define MAP_WIDTH 53

using namespace std;

void Gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Color(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}
int kb() { //키보드 입력값을 int형으로 "그대로" 반환
	int key;
	// 1- 49,  백 - 8
	key = _getch(); //키보드의 아스키값은 224 후에 다음 x 로 확장문자임
	return key;
}
void Draw_hp(Poketmon * player, Poketmon * com);
void Draw_name(Poketmon * player, Poketmon * com);  //이름과 레벨 같이 출력
void Draw_exp(Poketmon * player);
void Draw_status(Poketmon * player, Poketmon * com);
void Draw_skill_info(Poketmon * player, int skill_num);
void Draw_skill(Poketmon * player);
void Draw_life(int player_cnt, int com_cnt);
void Draw_line();
void Draw_text(string text,int  num);
void Draw_text(string poketmon,string text, int num);
void Draw_main_text(string text);
void Draw_reset(int i);
void Draw_p_list(vector<Poketmon*> player);
void Draw_bag(vector<Item*> bag);
void Draw_bag_info(vector<Item*> bag, int num);
void Draw_bag_info();
bool Check_use_Item(Poketmon * player , Item* bag); // 아이템이 선택한 포켓몬에게 효과가 있는지
void Draw_com(Poketmon * com);
bool random_check(int percent);

float Battle_type(Poketmon * attker, int skill_index);
float Battle_type(Poketmon * attker, Poketmon * deffend, int skill_index);
int Critical();
int Battle_atk(Poketmon * attker, Poketmon * deffend, int skill_index, bool who); //who가 true면 플레이어기준, false면 상대기준
bool Is_avd(Poketmon * attker, Poketmon * deffend, int skill_num);
bool Is_dead(Poketmon * poket);
void Draw_player(Poketmon * player);

int main() {

	vector<Poketmon*> player; player.push_back(피카츄); player.push_back(리자몽); player.push_back(이상해꽃); player.push_back(괴력몬); player.push_back(크로벳);
	vector<Poketmon*> onemock; onemock.push_back(네이티오); onemock.push_back(야도란); onemock.push_back(루주라); onemock.push_back(라프라스); onemock.push_back(나시);
	vector<Poketmon*> docksu; docksu.push_back(또가스); docksu.push_back(또도가스); docksu.push_back(질뻐기); docksu.push_back(도나리); docksu.push_back(크로벳);
	vector<Poketmon*> seba; seba.push_back(롱스톤); seba.push_back(홍수몬); seba.push_back(시라소몬); seba.push_back(롱스톤); seba.push_back(괴력몬);
	vector<Poketmon*> kanna; kanna.push_back(쥬레곤); kanna.push_back(파르셸); kanna.push_back(라프라스); kanna.push_back(쥬레곤); kanna.push_back(메꾸리);

	vector<vector<Poketmon*>> computer; computer.push_back(onemock);computer.push_back(docksu);computer.push_back(seba);computer.push_back(kanna);

	vector<Item*> player_Item; player_Item.push_back(&hyper_heal); player_Item.push_back(&rebirth); player_Item.push_back(&release_poison); player_Item.push_back(&release_electric); player_Item.push_back(&speed_up);
	Item * select_Item = &hyper_heal;
	
	Title t;
	


	//목숨 
	int player_life = 5;
	int com_life = 5;
	//포켓몬 출전 인덱스
	int player_poket_num = 0;
	int com_poket_num = 0;
	//몇번째 사천왕인지
	int stage = 0;
	//플레이어가 선택을 완료했는지?
	bool fir_turn_end = false; // - 첫번째 선택,
	bool sec_turn_end = false; // - 두번째 선택
	//아이템을 적용할 포켓몬, 교체할 포켓몬 인덱스 저장
	int temp_poket = 0;
	//한마리 전투불능을 판단할 변수
	bool turn_end;
	//누가죽었는지에 따라 나오게할 포켓몬 출력 가리는 변수 // 0은 아무것도 없음 , -1은 상대가 포켓몬을 내보낸다. 1은 플레이어가 포켓몬선택해 내보낸다  //내보낼때 내보낼 포켓몬없으면 승리하거나 패배,
	int out_poket = 0;
	//누가 이겼는지?
	bool who_win = true; // false - 사천왕 승, true - 플레이어 승
	
	


	////TEST!!
	////player.at(player_poket_num)->set_temp_hp(1);
	//for (int i = 0; i < 3; i++) {
	//	(computer.at(1)).at(i)->set_temp_hp(1);
	//	(computer.at(2)).at(i)->set_temp_hp(1);
	//	(computer.at(3)).at(i)->set_temp_hp(1);
	//}

	//사천왕 타이틀 등장
	t.get_title(stage);
	Sleep(4000);
	system("cls");

	

	do{

		Draw_life(player_life, com_life);
		Draw_line();
		Draw_reset(3);
		
		switch (stage)
		{
		case 0: Draw_text("사천왕 일목이 싸움을 걸어왔다!", 1);break;
		case 1: Draw_text("사천왕 독수가 싸움을 걸어왔다!", 1);break;
		case 2: Draw_text("사천왕 시바가 싸움을 걸어왔다!", 1);break;
		case 3: Draw_text("사천왕 컨나가 싸움을 걸어왔다!", 1);break;
		default:break;
		}
		Sleep(1500);

		switch (stage)
		{
		case 0: Draw_text("일목", (computer.at(stage)).at(com_poket_num)->get_name(), 5); break;
		case 1: Draw_text("독수", (computer.at(stage)).at(com_poket_num)->get_name(), 5); break;
		case 2: Draw_text("시바", (computer.at(stage)).at(com_poket_num)->get_name(), 5); break;
		case 3: Draw_text("칸나", (computer.at(stage)).at(com_poket_num)->get_name(), 5); break;
		default:break;
		}
		Sleep(1000);
		Draw_com((computer.at(stage)).at(com_poket_num));
		Sleep(1000);

		Draw_text("나와라!", player.at(player_poket_num)->get_name(), 4);
		player.at(player_poket_num)->set_join_battle(true);
		Sleep(1000);

		Draw_name(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
		Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
		Draw_exp(player.at(player_poket_num));

		Sleep(1000);

		do{

			

			Draw_name(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
			Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
			Draw_exp(player.at(player_poket_num));
			Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
	
			Draw_life(player_life, com_life);
			Draw_line();
			Draw_reset(3);
			Draw_main_text("1. 싸우다    2. 가방\t  3. 포켓몬\t4. 도망치다");

			while (1) {
				player.at(player_poket_num)->set_join_battle(true);
				//플레이어가 어떤 선택지인지?
				int select_num = -1; // -1 = 선택없음  , 0 ~ 3 = 스킬 인덱스 , 5 = 가방, 10~ 14 교체

		
				//플레이어 독,화상 뎀 계산
				if(player.at(player_poket_num)->get_status() == 1 || player.at(player_poket_num)->get_status() == 3){
			
					//화상, 독은 전체 체력의 1/16으로 데미지는 같으니까 굳이 나눠서 데미지 계산할 필요는 없다
					player.at(player_poket_num)->Hp_sub(player.at(player_poket_num)->get_hp() / 8);
					//데미지 들어갔으니 체력바 갱신
					Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
					//각자 텍스트 출력
					if(player.at(player_poket_num)->get_status() == 1) Draw_text(player.at(player_poket_num)->get_name(),"독 데미지를 입었다!",1);
					if(player.at(player_poket_num)->get_status() == 3) Draw_text(player.at(player_poket_num)->get_name(), "화상 데미지를 입었다!",1);
					Sleep(1500);
					//Death point★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
					if (turn_end = Is_dead(player.at(player_poket_num))) { out_poket = 1; player_life--; break; }
				}
				//컴퓨터 독,화상,마비,얼음,잠듦 뎀 계산
				if ((computer.at(stage)).at(com_poket_num)->get_status() == 1 || (computer.at(stage)).at(com_poket_num)->get_status() == 3){

					//화상, 독은 전체 체력의 1/16으로 데미지는 같으니까 굳이 나눠서 데미지 계산할 필요는 없다
					(computer.at(stage)).at(com_poket_num)->Hp_sub((computer.at(stage)).at(com_poket_num)->get_hp() / 8);
					//데미지 들어갔으니 체력바 갱신
					Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
					//각자 텍스트 출력
					if ((computer.at(stage)).at(com_poket_num)->get_status() == 1) Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "독 데미지를 입었다!",1);
					if ((computer.at(stage)).at(com_poket_num)->get_status() == 3) Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "화상 데미지를 입었다!",1);
					Sleep(1500);
					//Death point★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
					if (turn_end = Is_dead((computer.at(stage)).at(com_poket_num))) { out_poket = -1; com_life--; break; }
				}

					//turn_end 가 true면 탈출
					do{
						system("cls");
						Draw_name(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
						Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
						Draw_exp(player.at(player_poket_num));
						Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));

						Draw_life(player_life, com_life);
						Draw_line();
						Draw_reset(3);
						Draw_main_text("1. 싸우다    2. 가방\t  3. 포켓몬\t4. 도망치다");

						int result = kb(); // 1 - 싸운다 , 2 - 가방 , 3 - 포켓몬 , 4 - 도망친다

						//싸우다 선택
						if (result == 49) {
							Draw_reset(3);
							Draw_skill(player.at(player_poket_num));
							
							while (1) {
								int result2 = kb();
								if (49 <= result2 && result2 <= 52) {
									Draw_reset(1);
									Draw_skill_info(player.at(player_poket_num), result2 - 49);
									select_num = result2 - 49; //캐릭터 명령어 해당 숫자 대입
								}
								//엔터일때
								else if (result2 == 13 && select_num != -1) { fir_turn_end = true; sec_turn_end = false; break; } //★★★ first만 true고 sec은 false로 초기화
								//백스페이스일때
								else if (result2 == 8) { break; }
							}
						}
						//가방 선택
						else if (result == 50) {
							system("cls");
							Draw_bag(player_Item);
							while (!fir_turn_end) {
								int result2 = kb();
								if (49 <= result2 && result2 <= player_Item.size() + 48) { // 개수 만큼
									Gotoxy(0, (2 * player_Item.size()) + 3);
									Draw_bag_info();
									Gotoxy(0, (2 * player_Item.size()) + 3);
									Draw_bag_info(player_Item, result2 - 49);
									select_num = 5;
									select_Item = player_Item.at(result2 - 49);
								}

								//아이템 선택시 엔터일때
								else if (result2 == 13 && select_num != -1) {

									system("cls");
									Draw_p_list(player);
									Gotoxy(0, 14); Color(YELLOW); cout << "\t      누구에게 사용하시겠습니까?"; Color(WHITE);

									int temp_result = 0;
									while (1) {
								
										int result3 = kb();

										//1 누르면 49 , 2누르면 50 3누르면 51
										if (49 <= result3 && result3 <= 53) {
											temp_result = result3;
											Draw_reset(4);
											Gotoxy(0, 13);
											cout << player.at(result3 - 49)->get_name() << "  \t 에게 사용하시겠습니까?";
											Gotoxy(0, 15);
											cout << "          [확인 - Enter] [취소 - BackSpace]";

										}
										//사용할 포켓몬 엔터일때
										else if (result3 == 13 && temp_result != 0) {

											bool check = Check_use_Item(player.at(temp_result - 49), select_Item); // -> true면 패스

											//사용가능이면 ,아이템 개수 소모후 탈출
											if (check) {
												temp_poket = temp_result - 49;
												select_num = 5; 
												select_Item->_many--;
												//개수 0이면 가방에서 제외
												if (select_Item->_many == 0) {
													player_Item.erase(player_Item.begin() + (temp_result - 49));
												}
												fir_turn_end = true; 
												sec_turn_end = true; break;
											}
											//사용불가능이면
											else {
												Draw_reset(4);
												Gotoxy(0, 14);
												cout << player.at(temp_result - 49)->get_name() << "  \t 에겐 효과가 없습니다.";
											}
										}
										//사용할 포켓몬 백스페이스일때
										else if (result3 == 8) { 
											select_num = -1;
											system("cls");
											Draw_bag(player_Item);
											break; 
										}
									}

								}

								//아이템 선택 백스페이스일때
								else if (result2 == 8) { select_num = -1; break; }
							}
					
						}
				
						//포켓몬(교체) 선택
						else if (result == 51) {
							system("cls");
							while(1){
								Draw_p_list(player);
								int result2 = kb();

								if (49 <= result2 && result2 <= 53 && player_poket_num != (result2-49) && player.at(result2 - 49)->get_status() != -1){ // 1 ~ 3까지 && 지금 나와있는 index != result2 여야함 && 빈사상태는 안됌
									Draw_reset(4);
									Gotoxy(0, 13);
									cout << player.at(result2 - 49)->get_name() << "  \t 으로 교체하시겠습니까?";
									Gotoxy(0, 15);
									cout<<"          [확인 - Enter] [취소 - BackSpace]";
									select_num = result2 - 39; //캐릭터 명령어 해당 숫자 대입
								}
								//엔터일때
								if (result2 == 13 && select_num != -1 ) { fir_turn_end = true; sec_turn_end = true; break; }
								//백스페이스일때
								if (result2 == 8) { select_num = -1; break; }
							}
						}
						//도망치다 선택
						else if (result == 52) {
						Draw_text("\t\t   도망칠 수 없다!",1);
						Sleep(1500);
						}
					} while (!fir_turn_end);
					fir_turn_end = false; //다시 바꿔주기? 해야해나?
			
					//가방에서 아이템 선택시!
					if (select_num == 5) {
				
						if (select_Item->_index == 0) { //하이퍼 회복약
							player.at(temp_poket)->Hp_plus(500);
							system("cls");
							Draw_p_list(player);
							Gotoxy(0, 14);
							cout << player.at(temp_poket)->get_name() << "  \t 는 체력을 회복했다!";
						}
						else if (select_Item->_index == 1) { //기력약
							player.at(temp_poket)->Hp_plus(player.at(temp_poket)->get_hp() / 2);
							player.at(temp_poket)->set_status(0);
							system("cls");
							Draw_p_list(player);
							Gotoxy(0, 14);
							cout << player.at(temp_poket)->get_name() << "  \t 는 기운을 회복했다!"; //TODO 라이프카운트 올리기
						}
						else if (select_Item->_index == 2) { //해독제
							player.at(temp_poket)->set_status(0);
							system("cls");
							Draw_p_list(player);
							Gotoxy(0, 14);
							cout << player.at(temp_poket)->get_name() << "  \t 는 독에서 벗어났다!";
						}
						else if (select_Item->_index == 3) { //마비치료제
							player.at(temp_poket)->set_status(0);
							system("cls");
							Draw_p_list(player);
							Gotoxy(0, 14);
							cout << player.at(temp_poket)->get_name() << "  \t 는 마비에서 벗어났다!";
							player.at(temp_poket)->set_fast(player.at(temp_poket)->get_fast() / 2);
						}
						else if (select_Item->_index == 4) { //스피드업
							player.at(temp_poket)->set_rank_fast(player.at(temp_poket)->get_rank_fast() + 1);
							system("cls");
							Draw_p_list(player);
							Gotoxy(0, 14);
							cout << player.at(temp_poket)->get_name() << "  \t 는 스피드가 올라갔다!";
						}
						Sleep(1500);
					}
			
					{//메인화면
						system("cls");
						Draw_name(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
						Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
						Draw_exp(player.at(player_poket_num));
						Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
						Draw_life(player_life, com_life);
						Draw_line();
					}

					//포켓몬 교체시!
					if (10 <= select_num && select_num <= 15) {
				
						Gotoxy(0, 15);
						cout<< "\t"<< player.at(player_poket_num)->get_name()<<" 돌아와!";
						Sleep(1500);
						system("cls");
						Draw_life(player_life, com_life);
						Draw_line();
						Draw_com((computer.at(stage)).at(com_poket_num));
						Gotoxy(0, 15);
						cout << "\t"<< "가랏! " << player.at(select_num - 10)->get_name()<<"!!";
						player_poket_num = select_num - 10;
						player.at(player_poket_num)->set_join_battle(true);
						Sleep(1000);
						Draw_name(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
						Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
						Draw_exp(player.at(player_poket_num));
						Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
						Sleep(1000);
					}

					//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
					//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

					//본격 전투 시작 모든스텟은 get_b_?? 로 계산한다!     //sec_turn_end 은 교체나 ,가방 선택시 true로 바뀐다 -> 플레이어 턴은 다 했다는 소리,  써드는 
					//위에서 아이템이나, 교체를 선택하지 않았을경우 && 내가 먼저 공격할 경우
					//플레이어가 선공일때의 플레이어 턴. 실행 시작점─────────────────────────────────────────────────────────────
					if (!sec_turn_end && player.at(player_poket_num)->get_b_fast() >= (computer.at(stage)).at(com_poket_num)->get_b_fast()) {

						//잠
						if (player.at(player_poket_num)->get_status() >= 5) {

							//잠 해제 확률 계산
							//true면 잠깬거임~
							if (random_check(((player.at(player_poket_num)->get_status()-4) * 25))) {
								Draw_text(player.at(player_poket_num)->get_name(), "잠에서 깼다!",1);
								player.at(player_poket_num)->set_status(0);//기본상태로 설정
								Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));//상태 재 출력
								Sleep(1500);
							}
							else {
								Draw_text(player.at(player_poket_num)->get_name(), "쿨쿨 잠들어 있다",1);
								player.at(player_poket_num)->set_status(player.at(player_poket_num)->get_status() + 1);//잠 스택 증가
								player.at(player_poket_num)->set_can_atk(false);
								Sleep(1500);
							}
						}
						//마비
						else if (player.at(player_poket_num)->get_status() == 2) {
							//마비 행동불능 확률 계산 (마비는 자연해제 불가능)
							//true면 행동불능임
							if (random_check(25)) {
								Draw_text(player.at(player_poket_num)->get_name(), "몸이 저려서 움직일 수 없다!",1);
								player.at(player_poket_num)->set_can_atk(false);
								Sleep(1500);
							}
						}
						//얼음
						else if (player.at(player_poket_num)->get_status() == 4) {
							//얼음 해제확률 계산
							//true면 해제된거임~
							if (random_check(20)) {
								Draw_text(player.at(player_poket_num)->get_name(), "몸을 감싸던 얼음이 녹았다!",2);
								player.at(player_poket_num)->set_status(0);//기본상태로 설정
								Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
								Sleep(1500);
							}
							else {
								Draw_text(player.at(player_poket_num)->get_name(), "얼어버려서 움직일 수 없다!",1);
								player.at(player_poket_num)->set_can_atk(false);
								Sleep(1500);
							}
						}
						//혼란 체크! 0이 기본상태니까 0보다 높으면 있는거 , 위의 상태변화에서 턴 종료되면 실행안되게
						if (player.at(player_poket_num)->get_confusion() > 0 && player.at(player_poket_num)->get_can_atk() == true) {

							//혼란 해제 확률 계산 ->true면 해제됨 false면 그대로 유지
							//해제됨
							if (random_check((player.at(player_poket_num)->get_confusion() * 25))) {
								player.at(player_poket_num)->set_confusion(0);
								Draw_text(player.at(player_poket_num)->get_name(), "혼란이 풀렸다!", 2);
								Sleep(1500);
							}
							//해제 못함
							else {
								Draw_text(player.at(player_poket_num)->get_name(), "혼란에 빠져있다!", 1);
								Sleep(1500);
								//자기자신을 공격!  -> 행동불능으로 변환해야함
								if (random_check(33)) {
									Draw_text("영문도 모른 채 자신을 공격했다!", 1);//Death point★★★★★★★★★★★★★★★★★★★★★★★★★★★
									//데미지 계산
									player.at(player_poket_num)->confuse_damage();
									Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
									if (turn_end = Is_dead(player.at(player_poket_num))) { out_poket = 1; player_life--; break; }
									player.at(player_poket_num)->set_confusion(player.at(player_poket_num)->get_confusion() + 1); //혼란 스택 증가
									Sleep(1500);
									player.at(player_poket_num)->set_can_atk(false);
								}
								//상대방 공격 -> 정상적으로 턴 진행
							}
						}

						//스킬이 실행될때
						if (player.at(player_poket_num)->get_can_atk() == true) {
							Draw_text(player.at(player_poket_num)->get_name(), (*player.at(player_poket_num)->get_skill() + select_num)->get_name(), 2);
							Sleep(1500);

							//TODO :명중햇는지 계산해야함~★★★★★
							if (Is_avd(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num), select_num)) {

								int t_damage = 0;
								//공격하는 스킬인지, 변화만 하는 스킬인지 
								if ((*player.at(player_poket_num)->get_skill() + select_num)->get_is_attack()) {
									t_damage = Battle_atk(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num), select_num,true); //데미지 계산
									//Death point★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
									if (turn_end = Is_dead((computer.at(stage)).at(com_poket_num))) { out_poket = -1; com_life--; break; }

								}

								//1.스킬타입이 2,3,4중 하나라면,  2. , 상대가 특수에 걸리지 않았으면(이건 무조건) (computer.at(stage)).at(com_poket_num)->get_status() == 0
								if ((*player.at(player_poket_num)->get_skill() + select_num)->get_atk_type() == 2 || (*player.at(player_poket_num)->get_skill() + select_num)->get_atk_type() == 3 || (*player.at(player_poket_num)->get_skill() + select_num)->get_atk_type() == 5) {

									//체력 회복류 인가???
									if ((*player.at(player_poket_num)->get_skill() + select_num)->get_heal() > 0) {

										//속성이 false 이면 전체체력비례 , [잠자기 , hp회복]
										if ((*player.at(player_poket_num)->get_skill() + select_num)->get_is_attack() == false) {

											//잠자기스킬
											if ((*player.at(player_poket_num)->get_skill() + select_num)->get_heal() == 100) {

												//이미 풀피면 효과가 없다..
												if (player.at(player_poket_num)->get_temp_hp() == player.at(player_poket_num)->get_hp()) {
													Draw_text(player.at(player_poket_num)->get_name(), "효과가 없었다..", 3);
												}
												//효과있을때
												else {
													player.at(player_poket_num)->Hp_plus(player.at(player_poket_num)->get_hp());
													Draw_text(player.at(player_poket_num)->get_name(), "모두 회복되었다!", 1);
													player.at(player_poket_num)->set_status(5);//잠듦으로바꿔줌
												}
											}
											//Hp회복
											else {
												player.at(player_poket_num)->Hp_plus(player.at(player_poket_num)->get_hp() / 2);
												Draw_text(player.at(player_poket_num)->get_name(), "체력을 회복했다!", 1);
											}
											Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num)); //hp출력
										}
										//기가드렝ㄹ인
										else {
											player.at(player_poket_num)->Hp_plus((t_damage / 100) * (*player.at(player_poket_num)->get_skill() + select_num)->get_heal());
											Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num)); //hp출력
											Draw_text(player.at(player_poket_num)->get_name(), "데미지를 흡수했다!", 1);
										}
										Sleep(1500);
									}

									//상태이상에 걸리게하는가? true면 걸리게함
									if ((*player.at(player_poket_num)->get_skill() + select_num)->get_is_strange()) {

										if (random_check((*player.at(player_poket_num)->get_skill() + select_num)->get_strange_num())) {


											switch ((*player.at(player_poket_num)->get_skill() + select_num)->get_strange_type())
											{
											case 1:
												//모든 상태이상에 걸려있을때와 아닐때 두가지 예외 처리 필요 / 기본이아니면댐
												if ((computer.at(stage)).at(com_poket_num)->get_status() !=  0 ) { Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "상태이상 효과를 줄 수 없다..", 3);}
												else{ Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "독에 걸렸다!", 1); (computer.at(stage)).at(com_poket_num)->set_status(1); }
												break;
											case 2:
												if ((computer.at(stage)).at(com_poket_num)->get_status() != 0) { Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "상태이상 효과를 줄 수 없다..", 3); }
												else { Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "마비되어 기술이 나오기 어려워졌다!", 1); (computer.at(stage)).at(com_poket_num)->set_fast((computer.at(stage)).at(com_poket_num)->get_fast()/2); (computer.at(stage)).at(com_poket_num)->set_status(2); }
												break;
											case 3:
												//얼음상태는 직접 거는게 없으므로 이미 걸려있으면 그냥 넘어가면 된다
												if ((computer.at(stage)).at(com_poket_num)->get_status() != 0) { Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "상태이상 효과를 줄 수 없다..", 3); }
												else{
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "얼어버려서 움직일 수 없다!", 1); (computer.at(stage)).at(com_poket_num)->set_status(4);
												}
												break;
											case 4:
												if ((computer.at(stage)).at(com_poket_num)->get_status() != 0) { Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "상태이상 효과를 줄 수 없다..", 3); }
												else{
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "화상을 입었다!", 1); (computer.at(stage)).at(com_poket_num)->set_atk((computer.at(stage)).at(com_poket_num)->get_atk() / 2); (computer.at(stage)).at(com_poket_num)->set_status(3);
												}
												break;
											case 5: 
												if ((computer.at(stage)).at(com_poket_num)->get_confusion() == 0) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "혼란에 빠졌다!", 1); 
													(computer.at(stage)).at(com_poket_num)->set_confusion(1);
												}
												else {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "이미 혼란에 빠져있다!", 1);
												}
												break;
											case 6:Draw_text(player.at(player_poket_num)->get_name(), "잠들어 버렸다!", 1); player.at(player_poket_num)->set_status(5); break;
											default: break;
											}
											Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
											Sleep(1500);
										}
									}

									//내능력치 계산 스코프 시작──────────────────────────────────
									if ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_my_stat() != 0) {

										//내려갈때
										if ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_my_stat() < 0) {
											switch ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_my_stat())
											{
											case -1:
												if ((player.at(player_poket_num)->get_rank_atk() - 1) == -6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "물리 공격력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_atk(player.at(player_poket_num)->get_rank_atk() - 1);
													Draw_text(player.at(player_poket_num)->get_name(), "물리 공격력이 내려갔다", 2);
												}
												break;
											case -2:
												if ((player.at(player_poket_num)->get_rank_s_atk() - 1) == -6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "특수 공격력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_s_atk(player.at(player_poket_num)->get_rank_s_atk() - 1);
													Draw_text(player.at(player_poket_num)->get_name(), "특수 공격력이 내려갔다..", 2);
												}
												break;
											case -3:
												if ((player.at(player_poket_num)->get_rank_def() - 1) == -6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "물리 방어력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_def(player.at(player_poket_num)->get_rank_def() - 1);
													Draw_text(player.at(player_poket_num)->get_name(), "물리 방어력이 내려갔다..", 2);
												}
												break;
											case -4:
												if ((player.at(player_poket_num)->get_rank_s_def() - 1) == -6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "특수 방어력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_s_def(player.at(player_poket_num)->get_rank_s_def() - 1);
													Draw_text(player.at(player_poket_num)->get_name(), "특수 방어력이 내려갔다..", 2);
												}
												break;
											case -5:
												if ((player.at(player_poket_num)->get_rank_fast() - 1) == -6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "스피드는 이미 최대로 내려간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_fast(player.at(player_poket_num)->get_rank_fast() - 1);
													Draw_text(player.at(player_poket_num)->get_name(), "스피드가 내려갔다..", 2);
												}
												break;
											case -6:
												if ((player.at(player_poket_num)->get_rank_avd() - 1) == -6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "회피율은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_avd(player.at(player_poket_num)->get_rank_avd() - 1);
													Draw_text(player.at(player_poket_num)->get_name(), "회피율이 내려갔다..", 2);
												}
												break;
											default: break;
											}
										}
										//올라갈때
										else if ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_my_stat() > 0) {
											switch ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_my_stat())
											{
											case 1:
												if ((player.at(player_poket_num)->get_rank_atk() + 1) == 6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "물리 공격력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_atk(player.at(player_poket_num)->get_rank_atk() + 1);
													Draw_text(player.at(player_poket_num)->get_name(), "물리 공격력이 올라갔다!", 2);
												}
												break;
											case 2:
												if ((player.at(player_poket_num)->get_rank_s_atk() + 1) == 6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "특수 공격력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_s_atk(player.at(player_poket_num)->get_rank_s_atk() + 1);
													Draw_text(player.at(player_poket_num)->get_name(), "특수 공격력이 올라갔다!", 2);
												}
												break;
											case 3:
												if ((player.at(player_poket_num)->get_rank_def() + 1) == 6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "물리 방어력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_def(player.at(player_poket_num)->get_rank_def() + 1);
													Draw_text(player.at(player_poket_num)->get_name(), "물리 방어력이 올라갔다!", 2);
												}
												break;
											case 4:
												if ((player.at(player_poket_num)->get_rank_s_def() + 1) == 6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "특수 방어력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_s_def(player.at(player_poket_num)->get_rank_s_def() + 1);
													Draw_text(player.at(player_poket_num)->get_name(), "특수 방어력이 올라갔다!", 2);
												}
												break;
											case 5:
												if ((player.at(player_poket_num)->get_rank_fast() + 1) == 6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "스피드는 이미 최대로 올라간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_fast(player.at(player_poket_num)->get_rank_fast() + 1);
													Draw_text(player.at(player_poket_num)->get_name(), "스피드가 올라갔다!", 2);
												}
												break;
											case 6:
												if ((player.at(player_poket_num)->get_rank_avd() + 1) == 6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "회피율은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_avd(player.at(player_poket_num)->get_rank_avd() + 1);
													Draw_text(player.at(player_poket_num)->get_name(), "회피율이 올라갔다!", 2);
												}
												break;
											default: break;
											}
										}
										Sleep(1500);
									}
									//"상대" 능력치 계산 스코프 시작──────────────────────────────────
									if ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_your_stat() != 0) {

										//내려갈때
										if ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_your_stat() < 0) {
											switch ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_your_stat())
											{
											case -1:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_atk() - 1) == -6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 공격력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_atk((computer.at(stage)).at(com_poket_num)->get_rank_atk() - 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 공격력이 내려갔다!", 2);
												}
												break;
											case -2:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_s_atk() - 1) == -6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 공격력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_s_atk((computer.at(stage)).at(com_poket_num)->get_rank_s_atk() - 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 공격력이 내려갔다!", 2);
												}
												break;
											case -3:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_def() - 1) == -6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 방어력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_def((computer.at(stage)).at(com_poket_num)->get_rank_def() - 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 방어력이 내려갔다!", 2);

												}break;
											case -4:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_s_def() - 1) == -6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 방어력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_s_def((computer.at(stage)).at(com_poket_num)->get_rank_s_def() - 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 방어력이 내려갔다!", 2);

												}break;
											case -5:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_fast() - 1) == -6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "스피드는 이미 최대로 내려간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_fast((computer.at(stage)).at(com_poket_num)->get_rank_fast() - 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "스피드가 내려갔다!", 2);

												}break;
											case -6:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_avd() - 1) == -6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "회피율은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_avd((computer.at(stage)).at(com_poket_num)->get_rank_avd() - 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "회피율이 내려갔다!", 2);

												}break;
											default: break;
											}
										}
										//상대 랭크가 올라갈때
										else if ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_your_stat() > 0) {

											switch ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_your_stat())
											{
											case 1:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_atk() + 1) == 6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 공격력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_atk((computer.at(stage)).at(com_poket_num)->get_rank_atk() + 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 공격력이 올라갔다!", 2);
												}break;
											case 2:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_s_atk() + 1) == 6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 공격력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_s_atk((computer.at(stage)).at(com_poket_num)->get_rank_s_atk() + 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 공격력이 올라갔다!", 2);
												}break;
											case 3:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_def() + 1) == 6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 방어력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_def((computer.at(stage)).at(com_poket_num)->get_rank_def() + 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 방어력이 올라갔다!", 2);
												}break;
											case 4:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_s_def() + 1) == 6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 방어력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_s_def((computer.at(stage)).at(com_poket_num)->get_rank_s_def() + 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 방어력이 올라갔다!", 2);
												}break;
											case 5:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_fast() + 1) == 6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "스피드는 이미 최대로 올라간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_fast((computer.at(stage)).at(com_poket_num)->get_rank_fast() + 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "스피드가 올라갔다!", 2);
												}break;
											case 6:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_avd() + 1) == 6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "회피율은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_avd((computer.at(stage)).at(com_poket_num)->get_rank_avd() + 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "회피율이 올라갔다!", 2);
												}break;
											default: break;
											}
										}
										Sleep(1500);
									}
								}
							}
							//공격이 빗나갔을때
							else {
							Draw_text("하지만 공격이 맞지 않았다..", 1);
							Sleep(1500);
							}
						}

						sec_turn_end = true;//다음을 위해 바꿔줌
					}//플레이어가 선공일때의 플레이어 턴. 끝나는 지점────────────────────────────────────────────────────────────

					//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
					//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

					//상대방의 턴. -무조건 실행 시작점────────────────────────────────────────────────────────────────────
					int select_com = rand() % 4;

					//잠 - 완료
					if ((computer.at(stage)).at(com_poket_num)->get_status() >= 5) {

						//잠 해제 확률 계산
						//true면 잠깬거임~
						if (random_check((((computer.at(stage)).at(com_poket_num)->get_status() - 4) * 25))) {
							Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "잠에서 깼다!", 1);
							(computer.at(stage)).at(com_poket_num)->set_status(0);//기본상태로 설정
							Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
							Sleep(1500);
						}
						else {
							Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "쿨쿨 잠들어 있다", 1);
							(computer.at(stage)).at(com_poket_num)->set_status((computer.at(stage)).at(com_poket_num)->get_status() + 1);//잠 스택 증가
							(computer.at(stage)).at(com_poket_num)->set_can_atk(false);
							Sleep(1500);
						}
					}
					//마비
					else if ((computer.at(stage)).at(com_poket_num)->get_status() == 2) {
						//마비 행동불능 확률 계산 (마비는 자연해제 불가능)
						//true면 행동불능임
						if (random_check(25)) {
							Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "몸이 저려서 움직일 수 없다!", 1);
							(computer.at(stage)).at(com_poket_num)->set_can_atk(false);
							Sleep(1500);
						}
					}
					//얼음
					else if ((computer.at(stage)).at(com_poket_num)->get_status() == 4) {
						//얼음 해제확률 계산
						//true면 해제된거임~
						if (random_check(20)) {
							Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "몸을 감싸던 얼음이 녹았다!", 2);
							(computer.at(stage)).at(com_poket_num)->set_status(0);//기본상태로 설정
							Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
							Sleep(1500);
						}
						else {
							Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "얼어버려서 움직일 수 없다!", 1);
							(computer.at(stage)).at(com_poket_num)->set_can_atk(false);
							Sleep(1500);
						}
					}
					//혼란 체크! 0이 기본상태니까 0보다 높으면 있는거 , 위의 상태변화에서 턴 종료되면 실행안되게
					if ((computer.at(stage)).at(com_poket_num)->get_confusion() > 0 && (computer.at(stage)).at(com_poket_num)->get_can_atk() == true) {

						//혼란 해제 확률 계산 ->true면 해제됨 false면 그대로 유지
						//해제됨
						if (random_check(((computer.at(stage)).at(com_poket_num)->get_confusion() * 25))) {
							(computer.at(stage)).at(com_poket_num)->set_confusion(0);
							Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "혼란이 풀렸다!", 2);
							Sleep(1500);
						}
						//해제 못함
						else {
							Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "혼란에 빠져있다!", 1);
							Sleep(1500);
							//자기자신을 공격!  -> 행동불능으로 변환해야함
							if (random_check(33)) {
								Draw_text("영문도 모른 채 자신을 공격했다!", 1);
								//데미지 계산
								(computer.at(stage)).at(com_poket_num)->confuse_damage();
								(computer.at(stage)).at(com_poket_num)->set_confusion((computer.at(stage)).at(com_poket_num)->get_confusion() + 1); //혼란 스택 증가
								Sleep(1500);
								(computer.at(stage)).at(com_poket_num)->set_can_atk(false);
								//Death point★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
								if (turn_end = Is_dead((computer.at(stage)).at(com_poket_num))) { out_poket = -1;  com_life--; break; }
							}
							//상대방 공격 -> 정상적으로 턴 진행

						}//bitmask
					}

					//스킬이 실행될때
					if ((computer.at(stage)).at(com_poket_num)->get_can_atk() == true) {
						Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), (*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_name(), 2);
						Sleep(1500);
						//명중계싼
						if (Is_avd((computer.at(stage)).at(com_poket_num), player.at(player_poket_num), select_com)) {
							int t_damage = 0;
							//공격하는 스킬인지, 변화만 하는 스킬인지 
							if ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_is_attack()) {
								t_damage = Battle_atk((computer.at(stage)).at(com_poket_num), player.at(player_poket_num), select_com, false); //데미지 계산
								//Death point★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
								if (turn_end = Is_dead(player.at(player_poket_num))) { out_poket = 1; player_life--; break; }
							}

							//1.스킬타입이 2,3,5중 하나라면
							if ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_atk_type() == 2 || (*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_atk_type() == 3 || (*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_atk_type() == 5) {

								//체력 회복류 인가???
								if ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_heal() > 0) {

									//속성이 false 이면 전체체력비례 , [잠자기 , hp회복]
									if ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_is_attack() == false) {


										//잠자기스킬
										if ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_heal() == 100) {

											//이미 풀피면 효과가 없다..
											if ((computer.at(stage)).at(com_poket_num)->get_temp_hp() == (computer.at(stage)).at(com_poket_num)->get_hp()) {
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "효과가 없었다..", 3);
											}
											//효과있을때
											else {
												(computer.at(stage)).at(com_poket_num)->Hp_plus((computer.at(stage)).at(com_poket_num)->get_hp());
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "모두 회복되었다!", 1);
												(computer.at(stage)).at(com_poket_num)->set_status(5);//잠듦으로바꿔줌
												Draw_hp(player.at(player_poket_num),(computer.at(stage)).at(com_poket_num));
											}
										}
										//Hp회복
										else {
											(computer.at(stage)).at(com_poket_num)->Hp_plus((computer.at(stage)).at(com_poket_num)->get_hp() / 2);
											Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "체력을 회복했다!", 1);
										}
										Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
									}
									//기가드렝ㄹ인
									else {
										(computer.at(stage)).at(com_poket_num)->Hp_plus((t_damage / 100) * (*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_heal());
										Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
										Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "데미지를 흡수했다!", 1);
									}
									Sleep(1500);
								}
								//상태이상에 걸리게하는가? true면 걸리게함
								if ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_is_strange()) {

									if (random_check((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_strange_num())) {
										switch ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_strange_type())
										{
										case 1:
											//같은 상태이상에 걸려있을때와 아닐때 두가지 예외 처리 필요
											if (player.at(player_poket_num)->get_status() != 0) { Draw_text(player.at(player_poket_num)->get_name(), "상태이상 효과를 줄 수 없다..", 3); }
											else { Draw_text(player.at(player_poket_num)->get_name(), "독에 걸렸다!", 1); player.at(player_poket_num)->set_status(1); }
											break;
										case 2:
											if (player.at(player_poket_num)->get_status() != 0) { Draw_text(player.at(player_poket_num)->get_name(), "상태이상 효과를 줄 수 없다..", 3); }
											else { Draw_text(player.at(player_poket_num)->get_name(), "마비되어 기술이 나오기 어려워졌다!", 1); player.at(player_poket_num)->set_fast(player.at(player_poket_num)->get_fast() / 2); player.at(player_poket_num)->set_status(2); }
											break;
										case 3:
											//얼음상태는 직접 거는게 없으므로 이미 걸려있으면 그냥 넘어가면 된다
											if (player.at(player_poket_num)->get_status() != 0) { Draw_text(player.at(player_poket_num)->get_name(), "상태이상 효과를 줄 수 없다..", 3); }
											else{
												Draw_text(player.at(player_poket_num)->get_name(), "얼어버려서 움직일 수 없다!", 1); player.at(player_poket_num)->set_status(4);
											}
											break;
										case 4:
											if (player.at(player_poket_num)->get_status() != 0) { Draw_text(player.at(player_poket_num)->get_name(), "상태이상 효과를 줄 수 없다..", 3); }
											else{
												Draw_text(player.at(player_poket_num)->get_name(), "화상을 입었다!", 1); player.at(player_poket_num)->set_atk(player.at(player_poket_num)->get_atk() / 2); player.at(player_poket_num)->set_status(3);
											}
											break;
										case 5:
											if (player.at(player_poket_num)->get_confusion() == 0) {
												Draw_text(player.at(player_poket_num)->get_name(), "혼란에 빠졌다!", 1);
												player.at(player_poket_num)->set_confusion(1);
											}
											else {
												Draw_text(player.at(player_poket_num)->get_name(), "이미 혼란에 빠져있다!", 1);
											}
											break;
										case 6:Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "잠들어 버렸다!", 1); (computer.at(stage)).at(com_poket_num)->set_status(5); break;
										default: break;
										}
										Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
										Sleep(1500);
									}
								}
								//내능력치 계산 스코프 시작──────────────────────────────────
								if ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_what_my_stat() != 0) {

									//내려갈때
									if ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_what_my_stat() < 0) {
										switch ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_what_my_stat())
										{
										case -1:
											if (((computer.at(stage)).at(com_poket_num)->get_rank_atk() - 1) == -6) {
												//더이상 내려가지 않습니다..
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 공격력은 이미 최대로 내려간듯하다..", 2);
											}
											else {
												(computer.at(stage)).at(com_poket_num)->set_rank_atk((computer.at(stage)).at(com_poket_num)->get_rank_atk() - 1);
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 공격력이 내려갔다", 2);
											}
											break;
										case -2:
											if (((computer.at(stage)).at(com_poket_num)->get_rank_s_atk() - 1) == -6) {
												//더이상 내려가지 않습니다..
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 공격력은 이미 최대로 내려간듯하다..", 2);
											}
											else {
												(computer.at(stage)).at(com_poket_num)->set_rank_s_atk((computer.at(stage)).at(com_poket_num)->get_rank_s_atk() - 1);
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 공격력이 내려갔다..", 2);
											}
											break;
										case -3:
											if (((computer.at(stage)).at(com_poket_num)->get_rank_def() - 1) == -6) {
												//더이상 내려가지 않습니다..
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 방어력은 이미 최대로 내려간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_def((computer.at(stage)).at(com_poket_num)->get_rank_def() - 1);
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 방어력이 내려갔다..", 2);
											}
											break;
										case -4:
											if (((computer.at(stage)).at(com_poket_num)->get_rank_s_def() - 1) == -6) {
												//더이상 내려가지 않습니다..
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 방어력은 이미 최대로 내려간듯하다..", 2);
											}
											else {
												(computer.at(stage)).at(com_poket_num)->set_rank_s_def((computer.at(stage)).at(com_poket_num)->get_rank_s_def() - 1);
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 방어력이 내려갔다..", 2);
											}
											break;
										case -5:
											if (((computer.at(stage)).at(com_poket_num)->get_rank_fast() - 1) == -6) {
												//더이상 내려가지 않습니다..
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "스피드는 이미 최대로 내려간듯하다..", 2);
											}
											else {
												(computer.at(stage)).at(com_poket_num)->set_rank_fast((computer.at(stage)).at(com_poket_num)->get_rank_fast() - 1);
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "스피드가 내려갔다..", 2);
											}
											break;
										case -6:
											if (((computer.at(stage)).at(com_poket_num)->get_rank_avd() - 1) == -6) {
												//더이상 내려가지 않습니다..
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "회피율은 이미 최대로 내려간듯하다..", 2);
											}
											else {
												(computer.at(stage)).at(com_poket_num)->set_rank_avd((computer.at(stage)).at(com_poket_num)->get_rank_avd() - 1);
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "회피율이 내려갔다..", 2);
											}
											break;
										default: break;
										}
									}
									//올라갈때
									else if ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_what_my_stat() > 0) {
										switch ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_what_my_stat())
										{
										case 1:
											if (((computer.at(stage)).at(com_poket_num)->get_rank_atk() + 1) == 6) {
												//더이상 내려가지 않습니다..
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 공격력은 이미 최대로 올라간듯하다..", 2);
											}
											else {
												(computer.at(stage)).at(com_poket_num)->set_rank_atk((computer.at(stage)).at(com_poket_num)->get_rank_atk() + 1);
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 공격력이 올라갔다!", 2);
											}
											break;
										case 2:
											if (((computer.at(stage)).at(com_poket_num)->get_rank_s_atk() + 1) == 6) {
												//더이상 내려가지 않습니다..
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 공격력은 이미 최대로 올라간듯하다..", 2);
											}
											else {
												(computer.at(stage)).at(com_poket_num)->set_rank_s_atk((computer.at(stage)).at(com_poket_num)->get_rank_s_atk() + 1);
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 공격력이 올라갔다!", 2);
											}
											break;
										case 3:
											if (((computer.at(stage)).at(com_poket_num)->get_rank_def() + 1) == 6) {
												//더이상 내려가지 않습니다..
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 방어력은 이미 최대로 올라간듯하다..", 2);
											}
											else {
												(computer.at(stage)).at(com_poket_num)->set_rank_def((computer.at(stage)).at(com_poket_num)->get_rank_def() + 1);
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 방어력이 올라갔다!", 2);
											}
											break;
										case 4:
											if (((computer.at(stage)).at(com_poket_num)->get_rank_s_def() + 1) == 6) {
												//더이상 내려가지 않습니다..
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 방어력은 이미 최대로 올라간듯하다..", 2);
											}
											else {
												(computer.at(stage)).at(com_poket_num)->set_rank_s_def((computer.at(stage)).at(com_poket_num)->get_rank_s_def() + 1);
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 방어력이 올라갔다!", 2);
											}
											break;
										case 5:
											if (((computer.at(stage)).at(com_poket_num)->get_rank_fast() + 1) == 6) {
												//더이상 내려가지 않습니다..
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "스피드는 이미 최대로 올라간듯하다..", 2);
											}
											else {
												(computer.at(stage)).at(com_poket_num)->set_rank_fast((computer.at(stage)).at(com_poket_num)->get_rank_fast() + 1);
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "스피드가 올라갔다!", 2);
											}
											break;
										case 6:
											if (((computer.at(stage)).at(com_poket_num)->get_rank_avd() + 1) == 6) {
												//더이상 내려가지 않습니다..
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "회피율은 이미 최대로 올라간듯하다..", 2);
											}
											else {
												(computer.at(stage)).at(com_poket_num)->set_rank_avd((computer.at(stage)).at(com_poket_num)->get_rank_avd() + 1);
												Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "회피율이 올라갔다!", 2);
											}
											break;
										default: break;
										}
									}
									Sleep(1500);
								}
								//"상대" 능력치 계산 스코프 시작──────────────────────────────────
								if ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_com)->get_what_your_stat() != 0) {
									//내려갈때 
									if ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_num)->get_what_your_stat() < 0) {
										switch ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_num)->get_what_your_stat())
										{
										case -1:
											if ((player.at(player_poket_num)->get_rank_atk() - 1) == -6) {
												Draw_text(player.at(player_poket_num)->get_name(), "물리 공격력은 이미 최대로 내려간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_atk(player.at(player_poket_num)->get_rank_atk() - 1);
												Draw_text(player.at(player_poket_num)->get_name(), "물리 공격력이 내려갔다!", 2);
											}
											break;
										case -2:
											if ((player.at(player_poket_num)->get_rank_s_atk() - 1) == -6) {
												Draw_text(player.at(player_poket_num)->get_name(), "특수 공격력은 이미 최대로 내려간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_s_atk(player.at(player_poket_num)->get_rank_s_atk() - 1);
												Draw_text(player.at(player_poket_num)->get_name(), "특수 공격력이 내려갔다!", 2);
											}
											break;
										case -3:
											if ((player.at(player_poket_num)->get_rank_def() - 1) == -6) {
												Draw_text(player.at(player_poket_num)->get_name(), "물리 방어력은 이미 최대로 내려간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_def(player.at(player_poket_num)->get_rank_def() - 1);
												Draw_text(player.at(player_poket_num)->get_name(), "물리 방어력이 내려갔다!", 2);

											}break;
										case -4:
											if ((player.at(player_poket_num)->get_rank_s_def() - 1) == -6) {
												Draw_text(player.at(player_poket_num)->get_name(), "특수 방어력은 이미 최대로 내려간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_s_def(player.at(player_poket_num)->get_rank_s_def() - 1);
												Draw_text(player.at(player_poket_num)->get_name(), "특수 방어력이 내려갔다!", 2);

											}break;
										case -5:
											if ((player.at(player_poket_num)->get_rank_fast() - 1) == -6) {
												Draw_text(player.at(player_poket_num)->get_name(), "스피드는 이미 최대로 내려간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_fast(player.at(player_poket_num)->get_rank_fast() - 1);
												Draw_text(player.at(player_poket_num)->get_name(), "스피드가 내려갔다!", 2);

											}break;
										case -6:
											if ((player.at(player_poket_num)->get_rank_avd() - 1) == -6) {
												Draw_text(player.at(player_poket_num)->get_name(), "회피율은 이미 최대로 내려간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_avd(player.at(player_poket_num)->get_rank_avd() - 1);
												Draw_text(player.at(player_poket_num)->get_name(), "회피율이 내려갔다!", 2);

											}break;
										default: break;
										}
									}
									//상대 랭크가 올라갈때 
									else if ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_num)->get_what_your_stat() > 0) {

										switch ((*(computer.at(stage)).at(com_poket_num)->get_skill() + select_num)->get_what_your_stat())
										{
										case 1:
											if ((player.at(player_poket_num)->get_rank_atk() + 1) == 6) {
												Draw_text(player.at(player_poket_num)->get_name(), "물리 공격력은 이미 최대로 올라간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_atk(player.at(player_poket_num)->get_rank_atk() + 1);
												Draw_text(player.at(player_poket_num)->get_name(), "물리 공격력이 올라갔다!", 2);
											}break;
										case 2:
											if ((player.at(player_poket_num)->get_rank_s_atk() + 1) == 6) {
												Draw_text(player.at(player_poket_num)->get_name(), "특수 공격력은 이미 최대로 올라간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_s_atk(player.at(player_poket_num)->get_rank_s_atk() + 1);
												Draw_text(player.at(player_poket_num)->get_name(), "특수 공격력이 올라갔다!", 2);
											}break;
										case 3:
											if ((player.at(player_poket_num)->get_rank_def() + 1) == 6) {
												Draw_text(player.at(player_poket_num)->get_name(), "물리 방어력은 이미 최대로 올라간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_def(player.at(player_poket_num)->get_rank_def() + 1);
												Draw_text(player.at(player_poket_num)->get_name(), "물리 방어력이 올라갔다!", 2);
											}break;
										case 4:
											if ((player.at(player_poket_num)->get_rank_s_def() + 1) == 6) {
												Draw_text(player.at(player_poket_num)->get_name(), "특수 방어력은 이미 최대로 올라간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_s_def(player.at(player_poket_num)->get_rank_s_def() + 1);
												Draw_text(player.at(player_poket_num)->get_name(), "특수 방어력이 올라갔다!", 2);
											}break;
										case 5:
											if ((player.at(player_poket_num)->get_rank_fast() + 1) == 6) {
												Draw_text(player.at(player_poket_num)->get_name(), "스피드는 이미 최대로 올라간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_fast(player.at(player_poket_num)->get_rank_fast() + 1);
												Draw_text(player.at(player_poket_num)->get_name(), "스피드가 올라갔다!", 2);
											}break;
										case 6:
											if ((player.at(player_poket_num)->get_rank_avd() + 1) == 6) {
												Draw_text(player.at(player_poket_num)->get_name(), "회피율은 이미 최대로 올라간듯하다..", 2);
											}
											else {
												player.at(player_poket_num)->set_rank_avd(player.at(player_poket_num)->get_rank_avd() + 1);
												Draw_text(player.at(player_poket_num)->get_name(), "회피율이 올라갔다!", 2);
											}break;
										default: break;
										}
									}
									Sleep(1500);
								}
							}
						}
						//공격이 빗나갔을때
						else {
							Draw_text("하지만 공격이 맞지 않았다..", 1);
							Sleep(1500);
						}
					}
					//상대방의 턴. - "끝" ──────────────────────────────────────────────────────────────────────────

					//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
					//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

					//선공을 했다면 실행되지않고 sec_turn_end가 true기 떄문, 선공하지 않으면 실행된다
					if (!sec_turn_end) {

						//잠
						if (player.at(player_poket_num)->get_status() >= 5) {

							//잠 해제 확률 계산
							//true면 잠깬거임~
							if (random_check(((player.at(player_poket_num)->get_status() - 4) * 25))) {
								Draw_text(player.at(player_poket_num)->get_name(), "잠에서 깼다!", 1);
								player.at(player_poket_num)->set_status(0);//기본상태로 설정
								Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));//상태 재 출력
								Sleep(1500);
							}
							else {
								Draw_text(player.at(player_poket_num)->get_name(), "쿨쿨 잠들어 있다", 1);
								player.at(player_poket_num)->set_status(player.at(player_poket_num)->get_status() + 1);//잠 스택 증가
								player.at(player_poket_num)->set_can_atk(false);
								Sleep(1500);
							}
						}
						//마비
						else if (player.at(player_poket_num)->get_status() == 2) {
							//마비 행동불능 확률 계산 (마비는 자연해제 불가능)
							//true면 행동불능임
							if (random_check(25)) {
								Draw_text(player.at(player_poket_num)->get_name(), "몸이 저려서 움직일 수 없다!", 1);
								player.at(player_poket_num)->set_can_atk(false);
								Sleep(1500);
							}
						}
						//얼음
						else if (player.at(player_poket_num)->get_status() == 4) {
							//얼음 해제확률 계산
							//true면 해제된거임~
							if (random_check(20)) {
								Draw_text(player.at(player_poket_num)->get_name(), "몸을 감싸던 얼음이 녹았다!", 2);
								player.at(player_poket_num)->set_status(0);//기본상태로 설정
								Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
								Sleep(1500);
							}
							else {
								Draw_text(player.at(player_poket_num)->get_name(), "얼어버려서 움직일 수 없다!", 1);
								player.at(player_poket_num)->set_can_atk(false);
								Sleep(1500);
							}
						}
						//혼란 체크! 0이 기본상태니까 0보다 높으면 있는거 , 위의 상태변화에서 턴 종료되면 실행안되게
						if (player.at(player_poket_num)->get_confusion() > 0 && player.at(player_poket_num)->get_can_atk() == true) {

							//혼란 해제 확률 계산 ->true면 해제됨 false면 그대로 유지
							//해제됨
							if (random_check((player.at(player_poket_num)->get_confusion() * 25))) {
								player.at(player_poket_num)->set_confusion(0);
								Draw_text(player.at(player_poket_num)->get_name(), "혼란이 풀렸다!", 2);
								Sleep(1500);
							}
							//해제 못함
							else {
								Draw_text(player.at(player_poket_num)->get_name(), "혼란에 빠져있다!", 1);
								Sleep(1500);
								//자기자신을 공격!  -> 행동불능으로 변환해야함
								if (random_check(33)) {
									Draw_text("영문도 모른 채 자신을 공격했다!", 1);
									//데미지 계산
									player.at(player_poket_num)->confuse_damage();
									Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
									player.at(player_poket_num)->set_confusion(player.at(player_poket_num)->get_confusion() + 1); //혼란 스택 증가
									Sleep(1500);
									player.at(player_poket_num)->set_can_atk(false);
									//Death point★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
									if (turn_end = Is_dead(player.at(player_poket_num))) { out_poket = 1;  player_life--; break; }
								}
								//상대방 공격 -> 정상적으로 턴 진행
							}
						}

						//스킬이 실행될때
						if (player.at(player_poket_num)->get_can_atk() == true) {
							Draw_text(player.at(player_poket_num)->get_name(), (*player.at(player_poket_num)->get_skill() + select_num)->get_name(), 2);
							Sleep(1500);

							//TODO :명중햇는지 계산해야함~★★★★★
							if (Is_avd(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num), select_num)) {

								int t_damage = 0;
								//공격하는 스킬인지, 변화만 하는 스킬인지 
								if ((*player.at(player_poket_num)->get_skill() + select_num)->get_is_attack()) {
									t_damage = Battle_atk(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num), select_num, true); //데미지 계산
									//Death point★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
									if (turn_end = Is_dead((computer.at(stage)).at(com_poket_num))) { out_poket = -1; com_life--; break; }
								}

								//1.스킬타입이 2,3,4중 하나라면,  2. , 상대가 특수에 걸리지 않았으면(이건 무조건) (computer.at(stage)).at(com_poket_num)->get_status() == 0
								if ((*player.at(player_poket_num)->get_skill() + select_num)->get_atk_type() == 2 || (*player.at(player_poket_num)->get_skill() + select_num)->get_atk_type() == 3 || (*player.at(player_poket_num)->get_skill() + select_num)->get_atk_type() == 5) {

									//체력 회복류 인가???
									if ((*player.at(player_poket_num)->get_skill() + select_num)->get_heal() > 0) {

										//속성이 false 이면 전체체력비례 , [잠자기 , hp회복]
										if ((*player.at(player_poket_num)->get_skill() + select_num)->get_is_attack() == false) {

											//잠자기스킬
											if ((*player.at(player_poket_num)->get_skill() + select_num)->get_heal() == 100) {

												//이미 풀피면 효과가 없다..
												if (player.at(player_poket_num)->get_temp_hp() == player.at(player_poket_num)->get_hp()) {
													Draw_text(player.at(player_poket_num)->get_name(), "효과가 없었다..", 3);
												}
												//효과있을때
												else {
													player.at(player_poket_num)->Hp_plus(player.at(player_poket_num)->get_hp());
													Draw_text(player.at(player_poket_num)->get_name(), "모두 회복되었다!", 1);
													player.at(player_poket_num)->set_status(5);//잠듦으로바꿔줌
												}
											}
											//Hp회복
											else {
												player.at(player_poket_num)->Hp_plus(player.at(player_poket_num)->get_hp() / 2);
												Draw_text(player.at(player_poket_num)->get_name(), "체력을 회복했다!", 1);
											}
											Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num)); //hp출력
										}
										//기가드렝ㄹ인
										else {
											player.at(player_poket_num)->Hp_plus((t_damage / 100) * (*player.at(player_poket_num)->get_skill() + select_num)->get_heal());
											Draw_hp(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num)); //hp출력
											Draw_text(player.at(player_poket_num)->get_name(), "데미지를 흡수했다!", 1);
										}
										Sleep(1500);
									}

									//상태이상에 걸리게하는가? true면 걸리게함
									if ((*player.at(player_poket_num)->get_skill() + select_num)->get_is_strange()) {

										if (random_check((*player.at(player_poket_num)->get_skill() + select_num)->get_strange_num())) {
											switch ((*player.at(player_poket_num)->get_skill() + select_num)->get_strange_type())
											{
											case 1:
												//같은 상태이상에 걸려있을때와 아닐때 두가지 예외 처리 필요
												if ((computer.at(stage)).at(com_poket_num)->get_status() != 0) { Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "상태이상 효과를 줄 수 없다..", 3); }
												else { Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "독에 걸렸다!", 1); (computer.at(stage)).at(com_poket_num)->set_status(1); }
												break;
											case 2:
												if ((computer.at(stage)).at(com_poket_num)->get_status() != 0) { Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "상태이상 효과를 줄 수 없다..", 3); }
												else { Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "마비되어 기술이 나오기 어려워졌다!", 1); (computer.at(stage)).at(com_poket_num)->set_fast((computer.at(stage)).at(com_poket_num)->get_fast() / 2); (computer.at(stage)).at(com_poket_num)->set_status(2); }
												break;
											case 3:
												//얼음상태는 직접 거는게 없으므로 이미 걸려있으면 그냥 넘어가면 된다
												if ((computer.at(stage)).at(com_poket_num)->get_status() != 0) { Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "상태이상 효과를 줄 수 없다..", 3); }
												else{
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "얼어버려서 움직일 수 없다!", 1); (computer.at(stage)).at(com_poket_num)->set_status(4);
												}
												break;
											case 4:
												if ((computer.at(stage)).at(com_poket_num)->get_status() != 0) { Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "상태이상 효과를 줄 수 없다..", 3); }
												else{
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "화상을 입었다!", 1); (computer.at(stage)).at(com_poket_num)->set_atk((computer.at(stage)).at(com_poket_num)->get_atk() / 2); (computer.at(stage)).at(com_poket_num)->set_status(3);
												}
												break;
											case 5:
												if ((computer.at(stage)).at(com_poket_num)->get_confusion() == 0) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "혼란에 빠졌다!", 1);
													(computer.at(stage)).at(com_poket_num)->set_confusion(1);
												}
												else {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "이미 혼란에 빠져있다!", 1);
												}
												break;
											case 6:Draw_text(player.at(player_poket_num)->get_name(), "잠들어 버렸다!", 1); player.at(player_poket_num)->set_status(5); break;
											default: break;
											}
											Draw_status(player.at(player_poket_num), (computer.at(stage)).at(com_poket_num));
											Sleep(1500);
										}
									}

									//내능력치 계산 스코프 시작──────────────────────────────────
									if ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_my_stat() != 0) {

										//내려갈때
										if ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_my_stat() < 0) {
											switch ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_my_stat())
											{
											case -1:
												if ((player.at(player_poket_num)->get_rank_atk() - 1) == -6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "물리 공격력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_atk(player.at(player_poket_num)->get_rank_atk() - 1);
													Draw_text(player.at(player_poket_num)->get_name(), "물리 공격력이 내려갔다", 2);
												}
												break;
											case -2:
												if ((player.at(player_poket_num)->get_rank_s_atk() - 1) == -6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "특수 공격력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_s_atk(player.at(player_poket_num)->get_rank_s_atk() - 1);
													Draw_text(player.at(player_poket_num)->get_name(), "특수 공격력이 내려갔다..", 2);
												}
												break;
											case -3:
												if ((player.at(player_poket_num)->get_rank_def() - 1) == -6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "물리 방어력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_def(player.at(player_poket_num)->get_rank_def() - 1);
													Draw_text(player.at(player_poket_num)->get_name(), "물리 방어력이 내려갔다..", 2);
												}
												break;
											case -4:
												if ((player.at(player_poket_num)->get_rank_s_def() - 1) == -6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "특수 방어력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_s_def(player.at(player_poket_num)->get_rank_s_def() - 1);
													Draw_text(player.at(player_poket_num)->get_name(), "특수 방어력이 내려갔다..", 2);
												}
												break;
											case -5:
												if ((player.at(player_poket_num)->get_rank_fast() - 1) == -6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "스피드는 이미 최대로 내려간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_fast(player.at(player_poket_num)->get_rank_fast() - 1);
													Draw_text(player.at(player_poket_num)->get_name(), "스피드가 내려갔다..", 2);
												}
												break;
											case -6:
												if ((player.at(player_poket_num)->get_rank_avd() - 1) == -6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "회피율은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_avd(player.at(player_poket_num)->get_rank_avd() - 1);
													Draw_text(player.at(player_poket_num)->get_name(), "회피율이 내려갔다..", 2);
												}
												break;
											default: break;
											}
										}
										//올라갈때
										else if ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_my_stat() > 0) {
											switch ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_my_stat())
											{
											case 1:
												if ((player.at(player_poket_num)->get_rank_atk() + 1) == 6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "물리 공격력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_atk(player.at(player_poket_num)->get_rank_atk() + 1);
													Draw_text(player.at(player_poket_num)->get_name(), "물리 공격력이 올라갔다!", 2);
												}
												break;
											case 2:
												if ((player.at(player_poket_num)->get_rank_s_atk() + 1) == 6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "특수 공격력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_s_atk(player.at(player_poket_num)->get_rank_s_atk() + 1);
													Draw_text(player.at(player_poket_num)->get_name(), "특수 공격력이 올라갔다!", 2);
												}
												break;
											case 3:
												if ((player.at(player_poket_num)->get_rank_def() + 1) == 6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "물리 방어력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_def(player.at(player_poket_num)->get_rank_def() + 1);
													Draw_text(player.at(player_poket_num)->get_name(), "물리 방어력이 올라갔다!", 2);
												}
												break;
											case 4:
												if ((player.at(player_poket_num)->get_rank_s_def() + 1) == 6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "특수 방어력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_s_def(player.at(player_poket_num)->get_rank_s_def() + 1);
													Draw_text(player.at(player_poket_num)->get_name(), "특수 방어력이 올라갔다!", 2);
												}
												break;
											case 5:
												if ((player.at(player_poket_num)->get_rank_fast() + 1) == 6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "스피드는 이미 최대로 올라간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_fast(player.at(player_poket_num)->get_rank_fast() + 1);
													Draw_text(player.at(player_poket_num)->get_name(), "스피드가 올라갔다!", 2);
												}
												break;
											case 6:
												if ((player.at(player_poket_num)->get_rank_avd() + 1) == 6) {
													//더이상 내려가지 않습니다..
													Draw_text(player.at(player_poket_num)->get_name(), "회피율은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													player.at(player_poket_num)->set_rank_avd(player.at(player_poket_num)->get_rank_avd() + 1);
													Draw_text(player.at(player_poket_num)->get_name(), "회피율이 올라갔다!", 2);
												}
												break;
											default: break;
											}
										}
										Sleep(1500);
									}
									//"상대" 능력치 계산 스코프 시작──────────────────────────────────
									if ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_your_stat() != 0) {

										//내려갈때
										if ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_your_stat() < 0) {
											switch ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_your_stat())
											{
											case -1:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_atk() - 1) == -6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 공격력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_atk((computer.at(stage)).at(com_poket_num)->get_rank_atk() - 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 공격력이 내려갔다!", 2);
												}
												break;
											case -2:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_s_atk() - 1) == -6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 공격력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_s_atk((computer.at(stage)).at(com_poket_num)->get_rank_s_atk() - 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 공격력이 내려갔다!", 2);
												}
												break;
											case -3:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_def() - 1) == -6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 방어력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_def((computer.at(stage)).at(com_poket_num)->get_rank_def() - 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 방어력이 내려갔다!", 2);

												}break;
											case -4:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_s_def() - 1) == -6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 방어력은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_s_def((computer.at(stage)).at(com_poket_num)->get_rank_s_def() - 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 방어력이 내려갔다!", 2);

												}break;
											case -5:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_fast() - 1) == -6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "스피드는 이미 최대로 내려간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_fast((computer.at(stage)).at(com_poket_num)->get_rank_fast() - 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "스피드가 내려갔다!", 2);

												}break;
											case -6:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_avd() - 1) == -6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "회피율은 이미 최대로 내려간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_avd((computer.at(stage)).at(com_poket_num)->get_rank_avd() - 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "회피율이 내려갔다!", 2);

												}break;
											default: break;
											}
										}
										//상대 랭크가 올라갈때
										else if ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_your_stat() > 0) {

											switch ((*player.at(player_poket_num)->get_skill() + select_num)->get_what_your_stat())
											{
											case 1:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_atk() + 1) == 6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 공격력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_atk((computer.at(stage)).at(com_poket_num)->get_rank_atk() + 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 공격력이 올라갔다!", 2);
												}break;
											case 2:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_s_atk() + 1) == 6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 공격력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_s_atk((computer.at(stage)).at(com_poket_num)->get_rank_s_atk() + 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 공격력이 올라갔다!", 2);
												}break;
											case 3:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_def() + 1) == 6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 방어력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_def((computer.at(stage)).at(com_poket_num)->get_rank_def() + 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "물리 방어력이 올라갔다!", 2);
												}break;
											case 4:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_s_def() + 1) == 6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 방어력은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_s_def((computer.at(stage)).at(com_poket_num)->get_rank_s_def() + 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "특수 방어력이 올라갔다!", 2);
												}break;
											case 5:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_fast() + 1) == 6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "스피드는 이미 최대로 올라간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_fast((computer.at(stage)).at(com_poket_num)->get_rank_fast() + 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "스피드가 올라갔다!", 2);
												}break;
											case 6:
												if (((computer.at(stage)).at(com_poket_num)->get_rank_avd() + 1) == 6) {
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "회피율은 이미 최대로 올라간듯하다..", 2);
												}
												else {
													(computer.at(stage)).at(com_poket_num)->set_rank_avd((computer.at(stage)).at(com_poket_num)->get_rank_avd() + 1);
													Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "회피율이 올라갔다!", 2);
												}break;
											default: break;
											}
										}
										Sleep(1500);
									}
								}
							}
							//공격이 빗나갔을때
							else {
								Draw_text("하지만 공격이 맞지 않았다..", 1);
								Sleep(1500);
							}
						}

						sec_turn_end = false;
					}//플레이어가 선공일때의 플레이어 턴. 끝나는 지점────────────────────────────────────────────────────────────

					player.at(player_poket_num)->set_can_atk(true);
					(computer.at(stage)).at(com_poket_num)->set_can_atk(true);
			} 


			//상대가 죽어서 포켓몬 내보낼때
			if (out_poket == -1) {

				//~는 기절했다!
				Draw_text((computer.at(stage)).at(com_poket_num)->get_name(), "기절했다!", 1);
				Sleep(1500);
				system("cls");
				Draw_life(player_life, com_life);
				Draw_line();
				Draw_player(player.at(player_poket_num));


				//경험치 획득
				if (out_poket == -1) {
					for (int i = 0; i < 5; i++) {
						bool is_lv = false;
						if (player.at(i)->get_join_battle() && player.at(i)->get_status() != -1) {
							is_lv = player.at(i)->Exp_plus(37);
							Draw_text(player.at(i)->get_name(), "경험치를 획득했다!", 1);
							player.at(i)->set_join_battle(false);
							//경험치 다시그려~
							Draw_exp(player.at(player_poket_num));
							Sleep(1500);
							if (player.at(i)->get_exp() >= 100) {
								player.at(i)->set_exp(player.at(i)->get_exp() - 100);
								Draw_exp(player.at(player_poket_num));
							}
							if (is_lv) {
								player.at(i)->Lv_up();
								Draw_text(player.at(i)->get_name(), "레벨업을 했다!", 1);
								Draw_player(player.at(player_poket_num));
								Sleep(1500);
							}
						}
					}
				}

				if (com_life == 0) {
					who_win = true;
					break;
				}

				//포켓몬 번호 바꿈
				com_poket_num++;

				switch (stage)
				{
				case 0: Draw_text("일목", (computer.at(stage)).at(com_poket_num)->get_name(), 5); break;
				case 1: Draw_text("독수", (computer.at(stage)).at(com_poket_num)->get_name(), 5); break;
				case 2: Draw_text("시바", (computer.at(stage)).at(com_poket_num)->get_name(), 5); break;
				case 3: Draw_text("칸나", (computer.at(stage)).at(com_poket_num)->get_name(), 5); break;
				default:break;
				}
				Sleep(1000);
				Draw_com((computer.at(stage)).at(com_poket_num));
				Sleep(1000);
				out_poket = 0;//다음위해 초기화
			}
			//내가 죽어서 포켓몬 내보낼때
			else if (out_poket == 1) {

				//포켓몬 기절상태로 변환하기
				player.at(player_poket_num)->set_status(-1);

				//~는 기절했다!
				Draw_text(player.at(player_poket_num)->get_name(), "기절했다!", 1);
				Sleep(500);
				Draw_life(player_life, com_life);
				Sleep(1500);

				if (player_life == 0) {
					who_win = false;
					break;
				}

				system("cls");
				Draw_p_list(player);
				Gotoxy(0, 14); Color(YELLOW); cout << "\t       누구로 교체하시겠습니까?"; Color(WHITE);

				//플레이어는 선택지 있어야함!
				int temp_result = 0;
				while (1) {

					int result3 = kb();

					//1 누르면 49 , 2누르면 50 3누르면 51
					if (49 <= result3 && result3 <= 53) {
						temp_result = result3;
						Draw_reset(4);
						Gotoxy(0, 13);
						cout << player.at(result3 - 49)->get_name() << "  \t 로 교체하시겠습니까?";
						Gotoxy(0, 15);
						cout << "          [확인 - Enter] [취소 - BackSpace]";


					}
					//엔터눌렀을때(선택지하나라도 눌러야함)
					else if (result3 == 13 && temp_result != 0) {

						//사용할 포켓몬 엔터일때 -> 빈사상태면 안되고 현재포켓몬 안됨
						if (player.at(temp_result - 49)->get_temp_hp() != 0 && (temp_result - 49) != player_poket_num) {
							player_poket_num = (temp_result - 49);
							break;
						}
						//사용불가능이면
						else {
							Draw_reset(4);
							Gotoxy(0, 14);
							cout << player.at(temp_result - 49)->get_name() << "  \t 은 불가능 합니다.";
						}
					}
				}

				player.at(player_poket_num)->set_join_battle(true);

				system("cls");
				Draw_com((computer.at(stage)).at(com_poket_num));

				Draw_life(player_life, com_life);
				Draw_line();

				Draw_text("나와라!", player.at(player_poket_num)->get_name(), 4);
				Sleep(1500);

				Draw_player(player.at(player_poket_num));
				Sleep(1000);

				out_poket = 0;//다음위해 초기화
			}

		}while (1);

		//플레이어 패배시 게임종료
		if (who_win == false) {
			break;
		}
		else if (who_win == true) {

			//패배 멘트 후 다음스테이지 넘어가기
			com_life = 5; //컴퓨터 목숨 초기화
			out_poket = 0; //누가죽었는지 초기화
			player_poket_num = 0;
			com_poket_num = 0;

			switch (stage)
			{
			case 0: Draw_text("다음으로 넘어가 사천왕의 진정한 무서움을 확인하도록 해라!", 1);break;
			case 1: Draw_text("나도 자네도 더욱 위를 향해 정진할 뿐! 앞으로 나아가라!", 1);break;
			case 2: Draw_text("너와 포켓몬의 슈퍼 파워, 똑똑히 봤다!", 1);break;
			case 3: Draw_text("이런.. 다음번에는 각오하도록 해!", 1);break;
			default:break;
			}
			Sleep(4000);
			stage++;
			if (stage == 4) break;
			//진화 이벤트
			if (player.at(0)->get_lv() >= 50 && !(player.at(0)->get_evolution())) {

				t.evolotion();
				player.at(0)->set_name("라이츄");
				player.at(0)->Evolution_stat();
				player.at(0)->set_evolution(true);//진화했다고 변경
			}

			system("cls");
			t.get_title(stage);
			Sleep(4000);
			system("cls");
		}

	}while (1);


	Gotoxy(0, 23);
	cout << "탈출!!!!!!!!! selectNum : "<<who_win;
	return 0;

}

void Draw_name(Poketmon * player, Poketmon * com) {
	Color(WHITE);
	Gotoxy(1, 2);
	cout << "        ";
	Gotoxy(1, 2);
	cout << com->get_name()<<" Lv."<< com->get_lv();

	Gotoxy(41, 8);
	cout << "        ";
	Gotoxy(41, 8);
	cout << player->get_name();
	Gotoxy(34, 8);
	cout << "Lv."<<player->get_lv();
}

void Draw_status(Poketmon * player, Poketmon * com) {
	
	Gotoxy(18, 2);
	if (com->get_status() != 0 && com->get_status() < 5) {
		
		cout << "[";
		switch (com->get_status()) {
		case 1: Color(PURPLE); cout << " 독 "; break;
		case 2: Color(YELLOW); cout << "마비"; break;
		case 3: Color(RED); cout << "화상"; break;
		case 4: Color(SKY); cout << "얼음"; break;
		default: break;
		}
		Color(WHITE);
		cout << "]";

		
	}
	else if (com->get_status() >= 5) {
		Color(WHITE); cout << "[";
		Color(GRAY); cout << "잠듦";
		Color(WHITE); cout << "]";
	}
	else cout << "      ";
	Gotoxy(27, 8);
	if (player->get_status() != 0 && player->get_status() < 5) {
		cout << "[";
		switch (player->get_status()) {
		case 1: Color(PURPLE); cout << " 독 "; break;
		case 2: Color(YELLOW); cout << "마비"; break;
		case 3: Color(RED); cout << "화상"; break;
		case 4: Color(SKY); cout << "얼음"; break;
		default: break;
		}
		Color(WHITE);
		cout << "]";
	}
	else if (player->get_status() >= 5) {
		Color(WHITE); cout << "[";
		Color(GRAY); cout << "잠듦";
		Color(WHITE); cout << "]";
	}
	else cout << "      ";
}

void Draw_exp(Poketmon * player) {
	int temp = player->get_exp();
	//경험치 바
	Gotoxy(27, 12);
	cout << "━━━━━━━━━━━━━━━━━━━━";
	if (player->get_exp() != 0) {
		if (temp >= 100) temp = 100;
		temp /= 10;
		if (player->get_exp() < 10 && temp > 0) temp++;
	}
	else temp = 0;
	Color(BLUE);
	Gotoxy(27, 12);
	for (int i = 0; i < temp; i++) cout << "━━";
	Color(WHITE);
}

void Draw_hp(Poketmon * player, Poketmon * com) {
	
	int temp;

	Gotoxy(1, 4);
	cout << "                       ";
	Gotoxy(1, 4);
	Color(WHITE);
	cout << "HP:";
	//남은 체력에서 전체 체력 10/1을 나눔
	temp = (com->get_temp_hp()) / ((com->get_hp()) / 10);
	if ((com->get_temp_hp()) % ((com->get_hp()) / 10) > 0) temp++;

	if (temp <= 2)Color(RED);
	else if (temp <= 5)Color(YELLOW);
	else Color(GREAN);

	for (int i = 0; i < temp; i++) {
		cout << "■";
	}

	Color(WHITE);
	Gotoxy(27, 10);
	cout << "                       ";
	Gotoxy(27, 10);
	cout << "HP:";
	//남은 체력에서 전체 체력 10/1을 나눔
	temp = (player->get_temp_hp()) / ((player->get_hp()) / 10);
	if ((player->get_temp_hp()) % ((player->get_hp()) / 10) > 0) temp++;

	if (temp <= 2)Color(RED);
	else if (temp <= 5)Color(YELLOW);
	else Color(GREAN);

	for (int i = 0; i < temp; i++) {
		cout << "■";
	}

	//체력 숫자로 표시
	Color(WHITE);
	Gotoxy(35, 11);
	cout << "          ";
	Gotoxy(35, 11);
	if (player->get_temp_hp() <= 0) player->set_temp_hp(0);
	cout << player->get_temp_hp() << " / " << player->get_hp();
}

void Draw_line() {
	Gotoxy(0,14);
	for (int i = 1; i < MAP_WIDTH; i++) {
		printf("─");
	}
	Gotoxy(0, 16);
	for (int i = 1; i < MAP_WIDTH; i++) {
		printf("─");
	}
}

void Draw_skill_info(Poketmon * player, int skill_num) {

	Gotoxy(0, 15);
	if ((*player->get_skill() + skill_num)->get_atk_type() == 4) {

		cout << "위력 " << (*player->get_skill() + skill_num)->get_damage() << "%";
		cout << "\t명중률 " << (*player->get_skill() + skill_num)->get_hit_num() << "\t\t" << TYPE_NAME[(*player->get_skill() + skill_num)->get_type()] << "\t/";
	}
	else {
		cout << "위력 " << (*player->get_skill() + skill_num)->get_damage();
		cout << "   \t명중률 " << (*player->get_skill() + skill_num)->get_hit_num() << "\t\t" << TYPE_NAME[(*player->get_skill() + skill_num)->get_type()] << "\t/";
	}
	//공격스킬
	if ((*player->get_skill() + skill_num)->get_is_attack()) {
		if ((*player->get_skill() + skill_num)->get_atk_type() == 0 || (*player->get_skill() + skill_num)->get_atk_type() == 2) {
			cout << "물리";
		}
		else if ((*player->get_skill() + skill_num)->get_atk_type() == 1 || (*player->get_skill() + skill_num)->get_atk_type() == 3) cout << "특수";
		else if ((*player->get_skill() + skill_num)->get_atk_type() == 4) cout << "비례";
	}
	//only 변화스킬
	else {
		cout << "변화";
	}
}

void Draw_skill(Poketmon * player) {
	Gotoxy(0, 17);
	cout << "1." << (*player->get_skill() + 0)->get_name() << "\t\t2." << (*player->get_skill() + 1)->get_name() << endl<<endl;
	cout << "3." << (*player->get_skill() + 2)->get_name() << "\t\t4." << (*player->get_skill() + 3)->get_name() << endl;
}

void Draw_life(int player_cnt, int com_cnt) {
	
	Gotoxy(1, 0);
	Color(RED);
	for (int i = 0; i < com_cnt; i++) {
		cout << "◎ ";
	}
	Color(GRAY);
	for (int i = 5; i > com_cnt; i--) {
		cout << "◎ ";
	}

	Gotoxy(39, 13);
	Color(RED);
	for (int i = 0; i < player_cnt; i++) {
		cout << "◎ ";
	}
	Color(GRAY);
	for (int i = 5; i > player_cnt; i--) {
		cout << "◎ ";
	}
	Color(WHITE);
}

void Draw_text(string text, int num) { //1은 메인화면에서 가운데 텍스트, 2는 포켓몬 교체시 안내말위치
	if (num == 1) {
		Gotoxy(0, 15);
		cout << "                                                     ";
		Gotoxy(0, 15);
		cout << text;
	}
	if (num == 2) {
		Gotoxy(0, 10);
		cout << "                                                     ";
		Gotoxy(0, 10);
		cout << text;
	}
}
void Draw_text(string poketmon, string text,int num) { //1은 는(가)  , 2는 의 3은 에겐 4는 기본 5는 상대가 내보낼때

	Gotoxy(0, 15);
	cout << "                                                     ";
	Gotoxy(0, 15);
	if (num == 1) {	cout << "\"" << poketmon << "\"는(가) " << text;}
	else if (num == 2) { cout << "\"" << poketmon << "\"의 " << text << "!"; }
	else if (num == 3) { cout << "\"" << poketmon << "\"에겐 " << text << "!"; }
	else if (num == 4) { cout << poketmon << " " << text << "!"; }
	else if (num == 5) { cout  << poketmon << "는 " << text << "를(을) 내보냈다!"; }
	
}//오버로딩

void Draw_main_text(string text) {
	Gotoxy(0, 17);
	cout << "                                                     ";
	Gotoxy(0, 17);
	cout << text;
}

void Draw_reset(int i) {
	if (i == 1) {
		Gotoxy(0, 15);
		cout << "                                                     ";
	}
	else if (i == 2) {
		for (int i = 0;i < 5; i++) {

			Gotoxy(0, 17 + i);
			cout << "                                                     ";
		}
	}
	else if (i == 3) {
		Gotoxy(0, 15);
		cout << "                                                     ";
		for (int i = 0;i < 5; i++) {
			
			Gotoxy(0, 17 + i);
			cout << "                                                     ";
		}
	}
	else if (i == 4) {
		for (int i = 0;i < 3; i++) {
			Gotoxy(0, 13 + i);
			cout << "                                                     ";
		}
	}
}

void Draw_p_list(vector<Poketmon*> player) {

	for (int i = 0; i <= 12; i += 2) {
		Gotoxy(0, 0 + i);
		for (int j = 1; j < MAP_WIDTH+2; j++) {
			printf("─");
		}
	}

	Gotoxy(0, 16);
	for (int j = 1; j < MAP_WIDTH + 2; j++) {
		printf("─");
	}
	int index = 0;
	for (int i = 1; i <= 9; i+=2) {
		Gotoxy(0 , i);

		if (player.at(index)->get_status() == -1) Color(GRAY);
		else  Color(WHITE);

		cout << index + 1 << "." << player.at(index)->get_name() << "  \t ";
		switch (player.at(index)->get_status()) {
		case -1: Color(GRAY); cout << "[빈사]"; break;
		case 0: Color(WHITE); cout << "      "; break;
		case 1: Color(PURPLE); cout << "[ 독 ]"; break;
		case 2: Color(YELLOW); cout << "[마비]"; break;
		case 3: Color(RED); cout << "[화상]"; break;
		case 4: Color(SKY); cout << "[얼음]"; break;
		case 5: Color(GRAY); cout << "[잠듦]"; break;
		}

		if(player.at(index)->get_status() != -1) Color(WHITE);

		cout << "  Lv." << player.at(index)->get_lv() << "\tHP:";

		//남은 체력에서 전체 체력 10/1을 나눔
		int temp = (player.at(index)->get_temp_hp()) / ((player.at(index)->get_hp()) / 10);
		if ((player.at(index)->get_temp_hp()) % ((player.at(index)->get_hp()) / 10) > 0) temp++;

		if (temp <= 2)Color(RED);
		else if (temp <= 5)Color(YELLOW);
		else Color(GREAN);

		for (int i = 0; i < temp; i++) {
			cout << "■";
		}

		index++;
	}
	Color(WHITE);
}

//TODO:포켓몬 교체 하시겠습니까 멘트 위치 옮기기, 선택지 5까지 늘ㄹ리기 , 가방에서도 똑가티 ㅋㅋㅋ

void Draw_bag(vector<Item*> bag) {
	cout << "가방" << endl;
	for (int j = 1; j < 20; j++) { printf("─"); }
	cout << endl;
	for (int i = 1; i <= bag.size(); i++) {
		cout << i<<"."<<bag.at(i-1)->_name <<"\tX"<< bag.at(i - 1)->_many<<endl<<endl;
	}
	for (int j = 1; j < 20; j++) { printf("─"); }

}

void Draw_bag_info() {
	cout << "                " << endl << "                                                 ";
}

void Draw_bag_info(vector<Item*> bag , int num) {
	cout << bag.at(num)->_name<<endl<<bag.at(num)->_info;
}

bool Check_use_Item(Poketmon * player, Item * bag) {
	
	switch (bag->_index)
	{
	case 0:
		if (player->get_temp_hp() == player->get_hp() || player->get_status() == -1) return false; //빈사상태포켓몬에게 사용 불가능, ㅡ최대체력일때 사용불가능
		else return true;
	case 1:
		if (player->get_status() != -1) return false;//빈사상태가 "아니면" 사용 불가능
		else return true;
	case 2:
		if (player->get_status() != 1) return false;//독 상태아니면 사용 불 가능
		else return true;
	case 3:
		if (player->get_status() != 2) return false;//마비 상태아니면 사용 불 가능
		else return true;
	case 4:
		if (player->get_rank_fast() < 5 && player->get_status() != -1) return true;//5랭크 이하만 사용가능 ,  빈사상태가 아니어야함
		else return false;
	default:
		break;
	}
	return false;
}


//포켓몬 교환시에만 컴퓨터만 출력할때 쓰는 단순 함수 
void Draw_com(Poketmon * com) {
	//체력
	{	
		int temp;

		Gotoxy(1, 4);
		cout << "                       ";
		Gotoxy(1, 4);
		Color(WHITE);
		cout << "HP:";
		//남은 체력에서 전체 체력 10/1을 나눔
		temp = (com->get_temp_hp()) / ((com->get_hp()) / 10);
		if ((com->get_temp_hp()) % ((com->get_hp()) / 10) > 0) temp++;

		if (temp <= 2)Color(RED);
		else if (temp <= 5)Color(YELLOW);
		else Color(GREAN);

		for (int i = 0; i < temp; i++) {
			cout << "■";
		}
	}
	//상태
	{
		Gotoxy(18, 2);
		if (com->get_status() != 0) {

			cout << "[";
			switch (com->get_status()) {
			case 1: Color(PURPLE); cout << " 독 "; break;
			case 2: Color(YELLOW); cout << "마비"; break;
			case 3: Color(RED); cout << "화상"; break;
			case 4: Color(SKY); cout << "얼음"; break;
			case 5: Color(GRAY); cout << "잠듦"; break;
			}
			Color(WHITE);
			cout << "]";
		}
		else cout << "      ";
	}
	//이름,레벨
	{
		Color(WHITE);
		Gotoxy(1, 2);
		cout << "        ";
		Gotoxy(1, 2);
		cout << com->get_name() << " Lv." << com->get_lv();
	}
}

void Draw_player(Poketmon * player) {
	//체력
	{
		int temp;

		Color(WHITE);
		Gotoxy(27, 10);
		cout << "                       ";
		Gotoxy(27, 10);
		cout << "HP:";
		//남은 체력에서 전체 체력 10/1을 나눔
		temp = (player->get_temp_hp()) / ((player->get_hp()) / 10);
		if ((player->get_temp_hp()) % ((player->get_hp()) / 10) > 0) temp++;

		if (temp <= 2)Color(RED);
		else if (temp <= 5)Color(YELLOW);
		else Color(GREAN);

		for (int i = 0; i < temp; i++) {
			cout << "■";
		}

		//체력 숫자로 표시
		Color(WHITE);
		Gotoxy(35, 11);
		cout << "          ";
		Gotoxy(35, 11);
		if (player->get_temp_hp() <= 0) player->set_temp_hp(0);
		cout << player->get_temp_hp() << " / " << player->get_hp();
	}
	//상태
	{
		Gotoxy(27, 8);
		if (player->get_status() != 0 && player->get_status() < 5) {
			cout << "[";
			switch (player->get_status()) {
			case 1: Color(PURPLE); cout << " 독 "; break;
			case 2: Color(YELLOW); cout << "마비"; break;
			case 3: Color(RED); cout << "화상"; break;
			case 4: Color(SKY); cout << "얼음"; break;
			default: break;
			}
			Color(WHITE);
			cout << "]";
		}
		else if (player->get_status() >= 5) {
			Color(WHITE); cout << "[";
			Color(GRAY); cout << "잠듦";
			Color(WHITE); cout << "]";
		}
		else cout << "      ";
	}
	//이름,레벨
	{
		Gotoxy(41, 8);
		cout << "        ";
		Gotoxy(41, 8);
		cout << player->get_name();
		Gotoxy(34, 8);
		cout << "Lv." << player->get_lv();
	}
	//경험치
	{
		int temp;
		//경험치 바
		Gotoxy(27, 12);
		cout << "━━━━━━━━━━━━━━━━━━━━";
		if (player->get_exp() != 0) {
			temp = (player->get_exp() / 10);
			if (player->get_exp() < 10 && temp > 0) temp++;
		}
		else temp = 0;
		Color(BLUE);
		Gotoxy(27, 12);
		for (int i = 0; i < temp; i++) cout << "━━";
		Color(WHITE);
	}
}

//true면 확률안에 들은거야 false면 못든거야
bool random_check(int percent) {// percent = 몇까지 나와야하는지
	srand((unsigned int)time(NULL));
	int num = (rand() % 100) + 1;
	//성공시
	if (num <= percent) return true;
	else return false;

}

//──────────────────────────배틀 함수

//자속 결정
float Battle_type(Poketmon * attker, int skill_index) {
	//타입이 같으면
	if (attker->get_type() == (*attker->get_skill() + skill_index)->get_type())  return 1.5f;
	else return 1.0f;
}
//속성별 배수 결정
float Battle_type(Poketmon * attker, Poketmon * deffend, int skill_index) {
	switch ((*attker->get_skill() + skill_index)->get_type())
	{
		//공격스킬 타입이 강하거나 약할때 정의
	case 0:
		if (deffend->get_type() == 2 || deffend->get_type() == 6) { return 2.0f; }
		else if (deffend->get_type() == 0 || deffend->get_type() == 1 || deffend->get_type() == 10) { return 0.5f; }
		else return 1.0f;
	case 1:
		if (deffend->get_type() == 2 || deffend->get_type() == 6) { return 2.0f; }
		else if (deffend->get_type() == 0 || deffend->get_type() == 1 || deffend->get_type() == 6) { return 0.5f; }
		else return 1.0f;
	case 2:
		if (deffend->get_type() == 1 || deffend->get_type() == 10) { return 2.0f; }
		else if (deffend->get_type() == 2 || deffend->get_type() == 0 || deffend->get_type() == 5 || deffend->get_type() == 6) { return 0.5f; }
		else return 1.0f;
	case 3:
		if (deffend->get_type() == 4 || deffend->get_type() == 5) { return 2.0f; }
		else if (deffend->get_type() == 3) { return 0.5f; }
		else return 1.0f;
	case 4:
		if (deffend->get_type() == 6 || deffend->get_type() == 8 || deffend->get_type() == 9 || deffend->get_type() == 10) { return 2.0f; }
		else if (deffend->get_type() == 5 || deffend->get_type() == 3) { return 0.5f; }
		else return 1.0f;
	case 5:
		if (deffend->get_type() == 2) { return 2.0f; }
		else if (deffend->get_type() == 5 || deffend->get_type() == 10) { return 0.5f; }
		else return 1.0f;
	case 6:
		if (deffend->get_type() == 2) { return 2.0f; }
		else if (deffend->get_type() == 0 || deffend->get_type() == 1 || deffend->get_type() == 6) { return 0.5f; }
		else return 1.0f;
	case 7:
		if (deffend->get_type() == 1) { return 2.0f; }
		else if (deffend->get_type() == 2 || deffend->get_type() == 7) { return 0.5f; }
		else return 1.0f;
	case 8:
		if (deffend->get_type() == 3) { return 2.0f; }
		else if (deffend->get_type() == 4 || deffend->get_type() == 8) { return 0.5f; }
		else return 1.0f;
	case 9:
		if (deffend->get_type() == 4 || deffend->get_type() == 10) { return 0.5f; }
		else return 1.0f;
	case 10:
		if (deffend->get_type() == 0 || deffend->get_type() == 6) { return 2.0f; }
		else if (deffend->get_type() == 4) { return 0.5f; }
		else return 1.0f;
	default:
		return 1.0f;
	}
}

//크리티컬 결정
int Critical() {
	int result;
	srand((unsigned int)time(NULL));
	result = rand() & 100;
	if (result < 20) return 2;
	else return 1;
}

int Battle_atk(Poketmon * attker, Poketmon * deffend, int skill_index,bool who) {
	int damage = 0;
	int cri = Critical();
	float type_atk = Battle_type(attker, deffend, skill_index);
	//물리 공격시
	if ((*attker->get_skill() + skill_index)->get_atk_type() == 0 || (*attker->get_skill() + skill_index)->get_atk_type() == 2) {
		damage = (attker->get_b_atk() * (*attker->get_skill() + skill_index)->get_damage() * cri / deffend->get_b_def());
		damage *= type_atk;
		damage *= Battle_type(attker, skill_index);
	}
	//특수 공격시
	else if ((*attker->get_skill() + skill_index)->get_atk_type() == 1 || (*attker->get_skill() + skill_index)->get_atk_type() == 3) {
		damage = (attker->get_b_s_atk() * (*attker->get_skill() + skill_index)->get_damage() * cri / deffend->get_b_s_def());
		damage *= type_atk;
		damage *= Battle_type(attker, skill_index);
	}
	//비례 공격시
	else if ((*attker->get_skill() + skill_index)->get_atk_type() == 4) {
		damage = (deffend->get_temp_hp() / 100) * (*attker->get_skill() + skill_index)->get_damage();
		if (damage < 100) damage = 100;
	}

	deffend->Hp_sub(damage);
	//플레이어가 공격시
	if (who) Draw_hp(attker, deffend); //hp출력
	else Draw_hp(deffend, attker);

	if ((*attker->get_skill() + skill_index)->get_atk_type() != 4 && (*attker->get_skill() + skill_index)->get_atk_type() != 5) {
		if (cri == 2) {
			Draw_text("급소에 맞았다!", 1);
			Sleep(1500);
		}
		if (type_atk == 2.0f) {
			Draw_text("효과가 굉장했다!", 1);
			Sleep(1500);
		}
		else if (type_atk == 0.5f) {
			Draw_text("효과가 별로인 듯하다...", 1);
			Sleep(1500);
		}
	}

	return damage;
}

bool Is_avd(Poketmon * attker, Poketmon * deffend, int skill_index) {
	
	if ((*attker->get_skill() + skill_index)->get_hit_num() == 100) return true;
	else  return random_check((*attker->get_skill() + skill_index)->get_hit_num() - deffend->get_b_avd()); 
}

//true면 죽었음을 의미 
bool Is_dead(Poketmon * poket) {
	if (poket->get_temp_hp() <= 0) return true;
	else return false;
}