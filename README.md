# 2022-05-yeeun.shim

2022년 5월 인턴십 프로젝트
TV Broadcast Solution 팀 인턴사원 심예은

## 프로젝트 목적
Mpeg2와 Mpeg4형식의 동영상을 변환하고 편집하여 숏폼컨텐츠를 제작한다.

## Git convention
### 1. Commit Message Format
- 모든 커밋 메시지는 다음과 같은 형식을 **반드시** 따르도록 한다.
```
<[BE] or [FE]> <type>: <message> <issue number>
```
- ex) <br> `[BE] feat: Add user login api #1`
<br> `[FE] fix: Fix bug to can't login using google login #2`
<br> `docs: Update README.md #3`

#### 2. BE / FE
|         type          |                 description                 |
| :-------------------: | :-----------------------------------------: |
|          BE           |         Backend 코드와 관련된 커밋          |
|          FE           |         Frontend 코드와 관련된 커밋         |
| X(아무것도 적지 않음) | Backend/Frontend와 관련없는 커밋 (ex. docs) |

#### 3. Type
|   type   |                                     description                                     |
| :------: | :---------------------------------------------------------------------------------: |
|   feat   |                            새로운 기능 구현에 대한 커밋                             |
|   fix    |                        수정 사항에 대한 커밋(ex. bug, typo)                         |
|   docs   |                       문서 작성에 대한 커밋(ex. 주석, README)                       |
|  style   | 간단한 수정 사항에 대한 커밋(ex. 코드 포맷팅, 세미콜론 누락, 코드 변경이 없는 경우) |
| refactor |                              코드 리펙토링에 대한 커밋                              |
|   test   |                              테스트 작성과 관련된 커밋                              |
|  chore   |                      위의 상황에 해당하지 않는 커밋(ex. 빌드 업무 수정, 패키지 매니저 수정)  |

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
