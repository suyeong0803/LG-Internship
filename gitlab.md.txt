# gitlab
소프트웨어 개발에서 출시 전 라이프사이클을 위한 통합된 하나의 플랫폼
## gitlab 기능
* 프로젝트 관리
git 원격 저장소에 소스코드를 저장하고 버전관리를 할 수 있다. 그룹을 생성하고 각 멤버들에게 권한을 부여해 협업할 수 있다.

* 이슈 관리
이슈 트래커와 이슈 보드 등을 이용해 이슈를 관리하고 커밋 시스템과 이슈를 연동할 수 있다. 내장 이슈 관리 기능 외에도 외부 이슈 관리 시스템과 연동하여 사용할 수 있다.

*  CI/CD (Continuous Integration 지속적 통합, Continuous Deployment 지속적 배포)
gitlab에서는 무료로 내장된 CI/CD를 가지고 있으며 이를 사용하여 빌드, 테스트 및 배포한다.

* Wiki
마크다운 문법을 이용해 작성하며 프로젝트와 관련된 문서를 관리할 수 있다. wiki 별도 git 저장소가 생성되어 로컬에서 작업해서 push하여 사용해도 된다.


## git 용어 
* 원격 저장소 (remote repository)
원격 서버에 있는 저장소

* 로컬 저장소 (local repository)
commit들이 영구적으로 저장되는 영역, 원격 저장소로부터 clone한 commit들이 존재하는 영역

* 작업 디렉토리
pc에서 현재 작업 중에 있는 디렉토리

* 스테이징 영역
작업한 내용이 올라가는 임시 저장 영역, commit을 준비하는 영역

* clone
원격 저장소에 있는 코드를 로컬 저장소에 복사하는 것

* commit
변경의 단위, 변경점을 로컬 저장소로 저장하는 과정

## git 사용방법
* 생성 및 연결
	```
	$ git init
	$ git remote add <저장소 이름> <url> 
	```

* clone
` $ git clone <url>`
* commit
	``` 
	$ git add <파일명> // 스테이징에 올리기
	$ git add . // 전체 파일 올리기
	$ git commit -m "커밋메세지"
	```
* push (원격 저장소로 커밋 이력을 저장)
` $ git push <저장소 이름> <브랜치 이름> `

* pull (원격 저장소의 변경 사항을 받아옴)
 `$ git pull <저장소 이름> <브랜치 이름>`

* branch
	```
	$ git branch <브랜치 이름> // 브랜치 생성
	$ git checkout <브랜치 이름> // 브랜치 이동
	```


