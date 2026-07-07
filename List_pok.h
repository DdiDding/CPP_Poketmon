#pragma once
#include <iostream>
#include "Poketmon.h"
#include "Type.h"
#include "List_skill.h"

//이름,타입,공격,방어,특공,특방,속도,회피,체력,레벨,경험치,진화유무,스킬 [총 13개]
//체력은 개체값에서 20배로 설정



/*플레이어*/
Skill skill_pica[4] = { 전광석화,전기자석파,HP회복,볼트태클 };
Poketmon * 피카츄 = new Poketmon("피카츄",TYPE::전기,95,70,90,70,95,18,1000,49,0,false, &skill_pica);
Skill skill_liza[4] = { 파괴광선,화염방사,잠자기,플레어드라이브 };
Poketmon * 리자몽= new Poketmon("리자몽", TYPE::불, 184, 178, 109, 85, 100, 15, 900, 53, 0, true, &skill_liza);
Skill skill_esang[4] = {몸통박치기,독가루,기가드레인,리프스톰};
Poketmon * 이상해꽃= new Poketmon("이상해꽃", TYPE::풀, 1000, 123, 1022, 120, 80, 6, 950, 57, 0, true, &skill_esang);



//사천왕 포켓몬, 3마리 씩───────────────────────────────────────────────────

/*일목 - 에스퍼*/
Skill skill_neai[4] = { 전광석화,이상한빛,미래예지,사이코키네시스 };
Poketmon * 네이티오 = new Poketmon("네이티오",TYPE::에스퍼,75,70,95,70,95,10,650,43,0,true,&skill_neai);
Skill skill_yado[4] = { 망각술,누르기,사이코키네시스,하이드로펌프};
Poketmon * 야도란 = new Poketmon("야도란", TYPE::에스퍼,75,110,100,80,30,10,950,46,0, true, &skill_yado);
Skill skill_luzu[4] = {악마의키스,냉동펀치,눈사태,사이코쇼크};
Poketmon * 루주라 = new Poketmon("루주라", TYPE::에스퍼, 50,35,115,95,95,15,650,49,0, true, &skill_luzu);
Skill skill_nasi[4] = { 기가드레인,사이코키네시스,사이코쇼크,리플렉터 };
Poketmon * 나시 = new Poketmon("나시", TYPE::풀, 95, 125, 85, 75, 55, 12, 750, 51, 0, true, &skill_nasi);
//TEXT
//포켓몬리그에 어서 오너라!나는 사천왕 일목.세계를 여행하며 에스퍼타입 포켓몬의 수행으로 세월을 보냈다.그리고 드디어 사천왕의 한 사람이 되었다!나는 더욱더 정진할 것이다!이대로 질 수는 없다!
//졌다고 해서 내 목표는 변하지 않는다.강한 트레이너가 되기 위해 더욱 수행에 힘쓸 뿐이다.너는 다음으로 넘어가 사천왕의 진정한 무서움을 확인하도록 해라!


/*독수 - 독*/

Skill skill_ddoga[4] = { 오물공격,스모그,몸통박치기,누르기};
Poketmon * 또가스 = new Poketmon("또가스", TYPE::독, 65, 95, 60, 45, 35, 15, 400, 47, 0, true,&skill_ddoga);
Skill skill_ddodo[4] = {오물공격,스모그,용해액,원더스팀 };
Poketmon * 또도가스 = new Poketmon("또도가스", TYPE::독, 95, 120, 85, 70, 60, 18, 650, 52, 0, true,&skill_ddodo);
Skill skill_zillbuck[4] = { 독가루,작아지기,오물공격,핥기};
Poketmon * 질뻐기 = new Poketmon("질뻐기", TYPE::독, 105, 75, 65, 100, 50, 10, 800, 56, 0, true, &skill_zillbuck);
Skill skill_donare[4] = { 독가루,사이코키네시스,그림자분신,흡혈 };
Poketmon * 도나리 = new Poketmon("도나리", TYPE::독, 65, 60, 90, 75, 90, 15, 500, 53, 0, true, &skill_donare);
Skill skill_crobet[4] = {독가루,방전,그림자분신,전광석화};
Poketmon * 크로벳 = new Poketmon("크로벳", TYPE::독, 90, 80, 70, 80, 130, 20, 600, 56, 0, true, &skill_crobet);

//TEXT
//상대에게 독을 퍼뜨려 손 쓸 틈도 없이 자멸시키는... 시노비 기술의 정수를 받아라!
//나도 자네도 더욱 위를 향해 정진할 뿐! 앞으로 나아가라!


/*시바 - 격투*/
Skill skill_long[4] = { 돌떨구기,분노,힘껏치기,단단해지기 };
Poketmon * 롱스톤= new Poketmon("롱스톤", TYPE::바위, 45, 160, 30, 45, 70, 6, 700, 48, 0, true, &skill_long);
Skill skill_hongsu[4] = { 냉동펀치,불꽃펀치,번개펀치,메가톤펀치};
Poketmon * 홍수몬= new Poketmon("홍수몬", TYPE::격투, 105, 79, 35, 110, 76, 20, 1000, 58, 0, true, &skill_hongsu);
Skill skill_sira[4] = { 점프킥,기충전,무릎차기,메가톤킥 };
Poketmon * 시라소몬= new Poketmon("시라소몬", TYPE::격투, 120, 53, 35, 110, 87, 25, 1000, 57, 0, true, &skill_sira);
Skill skill_guereck[4] = { 째려보기 , 기충전, 땅가르기, 지옥의바퀴 };
Poketmon * 괴력몬 = new Poketmon("괴력몬", TYPE::격투, 130, 80, 65, 85, 55, 10, 900, 62, 0, true, &skill_guereck);


//TEXT
//사람도 포켓몬도 싸우고 단련하면 끝없이 강해질 수 있지! 난 그렇게 단련한 격투포켓몬들과 함께 살아왔고! 앞으로도 그럴 것이다!
//너와 포켓몬의 슈퍼 파워, 똑똑히 봤다! 다음에는 너 자신을 단련해 보겠나?

/*칸나 - 얼음*/
Skill skill_jurea[4] = { 잠자기,거품광선,오로라빔,파도타기 };
Poketmon * 쥬레곤= new Poketmon("쥬레곤", TYPE::물, 70, 80, 70, 95, 70, 10, 800, 57, 0, true, &skill_jurea);
Skill skill_parshalle[4] = { 초음파,냉동빔,하이드로펌프,독찌르기 };
Poketmon * 파르셸 = new Poketmon("파르셸", TYPE::얼음, 95, 180, 85, 45, 70, 20, 1200, 59, 0, true, &skill_parshalle);
Skill skill_rap[4] = { 하이드로펌프,방전,눈보라,사이코키네시스};
Poketmon * 라프라스 = new Poketmon("라프라스", TYPE::얼음, 85, 80, 85, 95, 60, 5, 1500, 62, 0, true, &skill_rap);
Skill skill_meaggu[4] = { 지진,눈보라,이판사판태클,스톤샤워};
Poketmon * 메꾸리 = new Poketmon("메꾸리", TYPE::얼음, 130, 80, 70, 60, 80, 10, 1600, 65, 0, true, &skill_meaggu);

//TEXT
//나는 사천왕 칸나! 얼음포켓몬을 내보내면 대적할 사람이 없지!
//다음번에는 각오하도록 해!


