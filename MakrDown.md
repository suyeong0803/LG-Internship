# MarkDown
<br>

## 1. MarkDown
- 텍스트 기반의 마크업 언어로 쉽게 쓰고 읽을 수 있으며 HTML로 변환이 가능하다.

### 장점
- 간결하고 별도의 도구 없이 작성 가능
- 다양한 형태로 변환이 가능
- 텍스트 형식으로 저장되어 용량이 작음

### 단점
- 모든 HTML 마크업을 대신하지 못함
- 표준이 없기 때문에 도구에 따라 생성물이 다름

<br>

## 2. 사용 방법
### 2.1 Headers
- `H1`부터 `H6`까지 지원
- `#` 로 작성 가능
#### [ 작성 방법 ]
```
# H1
## H2
### H3
#### H4
##### H5
###### H6
```
#### [ 결과 ]
# H1
## H2
### H3
#### H4
##### H5
###### H6
<br>

### 2.2 BlockQuote
- 블럭 인용 문자
- `>` 로 작성 가능
#### [ 작성 방법 ]
```
>First BlockQuote
> > Second BlockQuote
> > > Third BlockQuote
```
#### [ 결과 ]
> First BlockQuote
> > Second BlockQuote
> > > Third BlockQuote

<br>

### 2.3 List
- `*`, `+`, `-` 로 순서 없는 리스트 작성 가능
- 혼합해서 사용 가능
#### [ 작성 방법 ]
```
* first
  * second
    * third
+ first
  + second
    + third
- first
  - second
    - third
* first
  + second
    - third
```
#### [ 결과 ]
* first
  * second
    * third
+ first
  + second
    + third
- first
  - second
    - third
* first
  + second
    - third

<br>

### 2.4 Code Block
- `.```.`로 작성 가능 ( 양 옆에 . 제외하고 )
#### [ 작성 방법 ]
```
  .```
  int main()
  {
    cout << "Hello World" << endl;
  }
  .```
```
#### [ 결과 ]
```
int main()
{
  cout << "Hello World" << endl;
}
```
<br>

### 2.5 Bold
- `**`로 작성 가능
#### [ 작성 방법 ]
```
**BOLD** BASIC
```
#### [ 결과 ]
**BOLD** BASIC
