# CI / CD (지속적 통합 / 지속적 제공)

## CI / CD ?
- 애플리케이션 개발 단계를 **자동화**하여 보다 짧은 주기로 고객에게 제공하는 방법
- 기본 개념 : 지속적인 **통합**, 지속적인 서비스 **제공**, 지속적인 **배포**
- 새로운 코드 통합으로 인해 발생하는 문제를 해결하기 위한 솔루션

## CI vs CD
- CI : 지속적 통합
  - 새로운 코드 변경 사항이 정기적으로 빌드 및 테스트 되어 **레포지토리에 통합**
  - 여러 명의 개발자가 동시에 코드 작업을 할 경우 **충돌 문제 해결**

- CD : 지속적 제공 / 지속적 배포
  - 지속적 제공 
    - 개발자 : 변경 사항이 테스트를 거쳐 레포지토리에 **자동 업로드**
    - 운영팀 : 레포지토리에서 실시간 프로덕션 환경으로 배포 가능
    - 개발팀과 운영팀 간의 가시성과 **커뮤니케이션 문제 해결**
     
  - 지속적 배포
    - 개발자의 변경 사항을 레포지토리에서 고객이 사용 가능한 프로덕션 환경까지 **자동 릴리스**
    - 운영팀의 수동 프로세스 문제를 해결해 프로세스 과부하 문제 해결
    - 파이프라인의 다음 단계를 자동화 -> 지속적 제공의 장점을 활용

![image](https://user-images.githubusercontent.com/77713203/172047985-73c3c9c8-dc02-4dc2-a5eb-fd35799d9220.png)

<br>

## CI/CD와 DevOps

- CI/CD는 [DevOps](DevOps)를 보완
- CI/CD 파이프라인을 통해 변경 사항을 빠르게 푸시하는 동시에 안정성 보장

<br>

## CI/CD 워크플로우

1. CI/CD 파이프라인 **구축** : 개발자가 완성된 소프트웨어 솔루션을 제공하기 위해 취해야 하는 모든 단계
   - 소프트웨어 소싱 , 빌드 , 테스트 , 배포
3. CI/CD 파이프라인 **자동화** : 파이프라인을 버전관리 및 소스 통제 시스템에 연결
![image](https://user-images.githubusercontent.com/77713203/172048177-715dab2a-5a5b-4be4-b7cc-45f8f101727a.png)


## 참조
- [https://www.redhat.com/ko/topics/devops/what-is-ci-cd](https://www.redhat.com/ko/topics/devops/what-is-ci-cd)
- [https://www.servicenow.kr/products/devops/what-is-cicd.html](https://www.servicenow.kr/products/devops/what-is-cicd.html)
