<<<<<<< HEAD
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
- MPEG2 vs MPEG4
=======
# 2022-05-yeeun.shim

2022년 5월 인턴십 프로젝트
TV Broadcast Solution 팀 인턴사원 심예은

## 프로젝트 목적
Mpeg2와 Mpeg4형식의 동영상을 변환하고 편집하여 숏폼컨텐츠를 제작한다.


## 개발 환경
* c++
* visual studio 2019
* ffmpeg 3.4.16

## 빌드 환경
* **ffmpeg 환경 변수 추가**


  ```
  시스템/고급시스템 설정/환경 변수 추가
  ```
* **filesystem 라이브러리 사용**
  ``` 
  프로젝트 속성/일반/C++ 언어 표준/미리보기 -최신 C++ 초안의 기능(/std:c++ latest)
  C/C++ /언어/C++ 언어 표준/미리보기 -최신 C++ 초안의 기능(/std:c++ latest)
  ```
  ![filesystem_1](/uploads/bd673542aade2581e55143e02833ccd1/filesystem_1.png)
  ![filesysystem_2](/uploads/ac6bcf6d9b8f299f7f532643b1b3292d/filesysystem_2.png)
  
* **gui 동작**
  ```
  링커/시스템/창(/SUBSYSTEM:WINDOWS)
  ```
  ![window](/uploads/bdaa6872b16c4fd9ce63426214deda37/window.png)

test
>>>>>>> 11cd1f6bdb032eccbfb743d8e3f9b1a0d05968a5
