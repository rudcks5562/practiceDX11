- 240623 : note
프레임워크 기본 
헤더파일 사전에 폴더로 정리해서 모아놓고
타입스, 밸류즈, 스트럭트 이렇게 헤더정의 하고
최종적으로 stdafx.h에서 전처리 헤더파일에 모아놓고 쓸만한 거 STL이나 DX관련 인클루드 해서 미리 컴파일된 헤더에 다 작성해서 편하게 개발하도록 환경 구성하는 테크닉 경험.
또한 빌드 출력물 위치를 지정하는 것과 외부 라이브러리의 헤더와 경로를 사전에 미리 만들어놓는 작업을 통해 외부라이브러리 환경도 만든다.
프로젝트 환경- 일반에서 출력디렉터리를 binaries이하로 지정
c++에서 추가포함 디렉터리에서 include폴더를 경로 지정하여 라이브러리 헤더파일 끌어오고
링커에서도 일반에서 추가 라이브러리 디렉터리에서 경로 알려줘서 라이브러리 실제 파일위치도 등록한다.
추가포함 디렉터리 경로 지정- 이하 모든 헤더 체크..
대충 라이브러리 환경 구성한다는 내용..

winAPI 간단히 건드려서 사각형 윈도우 뜨게하는데 까지 진행하였음.
#pragma comment ("lib","dx~~~")이런식으로 헤더에서 라이브러리 어떤거 쓸거다 하는거도 배웠음.

tex라는 라이브러리를 일단 경로에 다 넣어줬고 헤더도 추가함.

윈도우 api에서 창만 필요하기 때문에 문자열 초기화나 옵션등의 요소들 제거하는 과정도 거침.
겟메시지를 픽 메시지로  while문 내부를 변경함.

myregisterClass에 가서 옵션 뜨는거 null로 해주고 클래스네임 하드코딩으로 직접 입력.(왜 문자열 옆에 L을 붙인거지?-찾아보기)
지정크기 만들기 위해 windowRect를 사용해 800 600을 기존 전처리 헤더에서 끌어와 입력 후 이를 hwnd에 넣어준다.

대략적 노트필기 완료.
---