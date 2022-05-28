# GitLab
<br>

## 1. Git vs GitHub vs GitLab
 - **Git** : 소스코드 버전 관리 시스템
 - **GitHub** : 공개적으로 모든 코드를 업로드 해 오픈 소스 역할을 함
 - **GitLab** : 개인 또는 조직 간의 private GitHub
<br>

## 2. GitLab
### GitLab 장점
- 개발 뿐만 아니라 **이슈 트래킹**을 통해 모든 라이프 사이클 커버 가능
- 이슈 트래킹
  - 이슈 : 프로젝트에서 개선 또는 해결되어야 할 문제
  - 마일스톤 : 프로젝트에서 주요한 이벤트를 표시하는 기준점 ( 달성되어야 하는 특정 목표 )
- CI / CD : 새로운 코드 통합으로 발생하는 문제 해결 솔루션, 지속적인 자동화와 지속적인 모니터링
<br>

### GitLab 단점
- push / pull이 GitHub에 비해 빠르지 않음
<br>

## 3. 사용 방법
### 파일 관리하기
1. **clone** : Remote Repository에 있는 파일을 Local Repository로 가져 옴 <br>
`$ git clone REPOSITORY_URL`

2. **remote** : Local Repository를 Remoty Repository와 연결 <br>
`$ git remote add origin BRANCH`

3. **add** : Git이 관리하는 Staging Area로 파일을 업로드 <br>
`$ git add FILENAME`

4. **commit** : Staging Area에 있는 파일을 Local Repository로 업로드 <br>
`$ git commit -m 'COMMIT_MESSAGE'`

5. **push** : Local Repository에 있는 파일을 Remote Repository로 업로드 <br>
`$ git push origin BRANCH`

6. **pull** : Remote Repository에서 업데이트 된 파일을 가져옴 <br>
`$ git pull origin BRANCH`
