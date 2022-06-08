# 2022-05-yeeun.shim

2022년 5월 인턴십 프로젝트
TV Broadcast Solution 팀 인턴사원 심예은

## 프로젝트 목적
Mpeg2와 Mpeg4형식의 동영상을 변환하고 편집하여 숏폼컨텐츠를 제작할 수 있다.

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
