# LG-Internship

6/2
- 테스트 툴 : google test -> 적용하는 이유 / 테스트 방법을 찾아서 쓰기 (NULL이라던가 , 빅뱅이라던가)
- 용어 정의 잘 알아두기

6/3
- ui에 더 힘쓰는 게 나을지도
- 아니면 병렬 처리를 한다거나
- 성능 보강이나
- 컨버터를 인터페이스로 두고 상속 받아서 MPEG2 MPEG4 컨버터로 만들기
- 함수 길면 안 되고
- 기능 시작할 때나 함수 위에, 중요한 데에 주석 달아주기
- 쓸데없이 줄 띄우지 말고

6/3 - 6/6
- converter 모듈화 -> interface 따로 빼서 MPEG2 & MPEG4로 나눔
- UI 제작 -> Windows Api 사용해서 간단하게 만듦
- video1, video2도 클래스 모듈화 해서 그 안에 path랑 type 저장해 두고 check 함수 부르도록 수정
- boost 라이브러리 사용해 file extension 이나 file.exist 같은 거 썼음
    - boost 다운로드 -> bat 파일 다운로드 -> exe 파일 다운로드 -> c++ 일반 추가 디렉토리 C:\Users\원수영\Desktop\project\boost_1_79_0 -> 링커 일반 추가 라이브러리 stage\lib
- GUI
  - 속성 -> 고급 -> 문자집합 -> 멀티바이트
  - 링커 -> 시스템 -> 하위시스템 -> 창

6/7
- LLD 보강
- 파일 탐색기 불러오기
- 
