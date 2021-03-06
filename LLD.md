# 목차

- 1. [프로젝트 개요](#1-프로젝트-개요)
  - 1.1 [프로젝트 목적](#11-프로젝트-개요)

- 2. [아키텍쳐 드라이버](#2-아키텍쳐-드라이버)
  - 2.1 [제약사항](#21-제약사항)
    - 2.1.1 [기술적 제약사항](#211-기술적-제약사항)
  - 2.2 [기능적 요구사항](#22-기능적-요구사항)
  - 2.3 [비기능적 요구사항](#23-비기능적-요구사항)
    - 2.3.1 [품질 속성](#231-품질-속성)

- 3. [System Context](#3-system-context)

- 4. [아키텍처 설계](#4-아키텍처-설계)
  - 4.1 [Static Perspectives](#41-static-perspectives)
    - 4.1.1 [First Decomposition Diagram](#411-first-decomposition-diagram)
    - 4.1.2 [Second Decomposition Diagram](#411-second-decomposition-diagram)  
- 4.2 [Dynamic Perspectives](#42-dynamic-perspectives)
    - 4.2.1 [Sequence Diagrams](#421-sequence-diagrams)

<br>

# 1. 프로젝트 개요

## 1.1 프로젝트 목적

본 프로젝트의 목적은 MPEG2 형식의 TV 녹화 영상을 MPEG4 형식으로 **변환**하고 영상을 **병합**하여 숏폼 컨텐츠로 제작하여 영상처리 기술을 경험한다.
그 중 **변환** 기능을 중점으로 기술한다.
 
<br>

# 2. 아키텍쳐 드라이버

본 절에서는 High-Level Functional Requirements로부터 **동영상 편집 프로그램**에 대한 기술적 제약사항(technical- constraints), 기능 요구사항(functional requirements), 그리고 품질 요소(quality attribute)로 구성된 아키텍쳐 드라이버(architectural drivers)에 관해 기술한다. 

## 2.1 제약사항

## 2.1.1 기술적 제약사항

| ID | Constraints | Descriptions |
|----|-------------|--------------|
|TC01|설계 및 구현 제약|1. 이 시스템은 **C++** 언어를 사용한다. <br> 2. 이 시스템은 **Windows** 환경에서 개발한다.|
|TC02||1. 편집할 영상의 길이는 **00** 로 제한한다.|

<br>

## 2.2 기능적 요구사항

### [FR01] 불러오기

| 항목 | 내용 |
|------|------|
| 기본 동작 | 사용자가 원하는 파일을 불러온다. |
| 선행 조건 | - |
| 후행 조건 | 프로그램에 영상이 올라간다.|
| 기본 시나리오 | 1. 원하는 파일의 경로를 입력한다. <br> 2. 'check' 버튼을 누른다. |
| 대안 시나리오 | - |
| 예외 처리 | 1. **잘못된 경로**일 경우, "Please Check Your File Path!" 알림 메세지를 띄운다. <br> 2. 파일 경로가 **디렉토리**일 경우, "It is Directory!" 알림 메세지를 띄운다. <br> 3. 파일 확장자가 **mpg, mp4**가 아닐 경우, "Please Check File Extension!" 알림 메세지를 띄운다. <br> 4. 파일 경로를 **입력하지 않은** 경우, "Please Insert File Path!" 알림 메세지를 띄운다.|

### [FR02] 변환

| 항목 | 내용 |
|------|-----|
| 기본 동작 | 파일 형식을 변환한다. |
| 선행 조건 | 파일 경로를 입력한다. |
| 후행 조건 | 파일 형식이 변환된다. |
| 기본 시나리오 | 1. 변환을 요청한다. <br> 2. 변환 형식을 선택한다. <br> 3. 선택한 형식으로 변환한다. |
| 대안 시나리오 | - |
| 예외 처리 | 1. 변환 요청과 현재 **타입이 같은** 경우, "already TYPE!" 알림 메세지를 띄운다. (TYPE : 선택한 형식) <br> 2. 파일의 **유효 여부**를 검사하지 않은 경우, "Please Press Check Button!" 알림 메세지를 띄운다. <br> 3. 변환 **형식을 선택하지 않은** 경우, "Please Check Converting Type!" 알림 메세지를 띄운다. |

### [FR03] 병합

| 항목 | 내용 |
|------|-----|
| 기본 동작 | 2개의 파일을 병합한다. |
| 선행 조건 | 프로그램에 영상이 2개 존재해야 한다.|
| 후행 조건 | 2개의 파일이 하나의 파일로 병합된다. |
| 기본 시나리오 | 1. 영상 추출을 요청한다. <br> 2. 파일이 병합된다.|
| 대안 시나리오 | - |
| 예외 처리 | 1. 두 파일의 형식이 다를 경우, "파일 형식이 일치하지 않습니다." 알림 메세지를 띄운다. |
 
### [FR04] 추출

| 항목 | 내용 |
|------|-----|
| 기본 동작 | 파일을 로컬에 저장한다. |
| 선행 조건 | 병합이 이루어질 수 있는 환경이어야 한다. |
| 후행 조건 | 지정된 경로와 이름으로 파일이 저장된다. |
| 기본 시나리오 | 1. 추출을 요청한다. <br> 2. 동영상 저장 위치를 입력한다. <br> 3. 지정 위치로 병합된 동영상이 저장된다. |
| 대안 시나리오 | - |
| 예외 처리 | 1. **저장 경로가 존재하지 않을 경우** "해당 경로가 없습니다" 알림 메세지를 띄운다. <br> 2. **중복된 파일 이름**이 있을 경우 "이미 존재하는 이름입니다." 알림 메세지를 띄운다. |

 <br>

## 2.3 비기능적 요구사항

### 2.3.1 품질 속성

 
| ID | 품질속성 | 설명 |
|----|----------|------|
|QA01| 정확성 | 제공하는 서비스는 사용자가 원하는 결과물과 실제 결과물이 동일해야 한다. |
|QA02| 신뢰성 | 서비스가 비정상적으로 종료 시 사용자가 소유하고 있던 자료에 영향이 없어야 한다.|
|QA03| 유지보수성 | 새로운 기능 추가 시 기존 프로그램에 영향이 없어야 한다. |

<br>

# 3. System Context
<br>

# 4. 아키텍처 설계
## 4.1 Static Perspectives
### 4.1.1 First Decomposition Diagram
![first_decomposition](uploads/cd59d5bb8567890335824e9acf056046/first_decomposition.png)

### 4.1.2 Second Decomposition Diagram
#### Convert
![second_decomposition](uploads/7088593a14496ab325a5b7f6deca8674/second_decomposition.png)

## 4.2 Dynamic Perspectives
### 4.2.1 Sequence Diagrams
#### Convert
![sequence_diagram_convert](uploads/c1d200c099462dd5506fce64244d25f8/sequence_diagram_convert.png)

- Merge

![sequence_diagram_merge](uploads/d99fb3522171772431b8c2466177eeef/sequence_diagram_merge.png)

<br>

