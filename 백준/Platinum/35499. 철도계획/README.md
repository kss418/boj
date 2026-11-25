# [Platinum V] 철도계획 - 35499 

[문제 링크](https://acmicpc.net/problem/35499) 

### 성능 요약

메모리: 11964 KB, 시간: 74 ms

### 분류

자료 구조, 분리 집합, 그래프, 그리디, 최소 스패닝 트리

### 제출 일자

2026년 11월 25일 09:18:39

### 문제 설명

<p>국민대학교에는 철도가 없어 많은 학생이 버스를 타고 등하교한다. 학교에서는 학생들의 편의를 위해 새로운 철도망을 구축하기로 했다.</p>

<p>현재 계획된 역 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N$</span></mjx-container>개가 있으며, 철도를 건설할 수 있는 후보 구간 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D440 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>M</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$M$</span></mjx-container>개가 존재한다. 각 철도 구간은 서로 다른 두 역을 양방향으로 연결하며, 이를 건설하여 운행하면 그에 따른 예상 수익을 얻는다.</p>

<p>학교는 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D440 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>M</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$M$</span></mjx-container>개의 후보 구간 중 일부를 선택하여 철도망을 구축하려 한다. 단, 너무 많은 철도를 건설하면 운영상의 문제가 생기므로 다음 규칙들을 반드시 지켜야 한다.</p>

<ul>
<li>노선이란 서로 연결된 철도 구간들의 집합을 의미한다. 두 철도 구간이 하나의 역을 공유한다면 두 구간은 직접 연결되어 있으며, 직접 또는 간접적으로 연결된 모든 철도 구간은 같은 노선에 속한다.</li>
<li>여러 개의 독립된 노선이 존재할 수 있으며, 어떠한 노선에도 연결되지 않은 역이 존재할 수 있다.</li>
<li>하나의 노선 안에는 순환 경로가 최대 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mn class="mjx-n"><mjx-c class="mjx-c31"></mjx-c></mjx-mn></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mn>1</mn></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$1$</span></mjx-container>개 존재할 수 있다.
<ul>
<li>어떤 역에서 출발하여 서로 다른 철도 구간들을 거쳐 출발한 역으로 다시 돌아오는 경로를 순환 경로라고 한다.</li>
<li>두 순환 경로가 다르다는 것은, 경로에 포함된 철도 구간의 집합이 서로 다름을 의미한다.</li>
</ul>
</li>
</ul>

<p>이 규칙들을 지키면서 철도를 만들 때, 예상 수익의 합의 최댓값을 구해보자.</p>

### 입력 

 <p>첫 번째 줄에 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N$</span></mjx-container>과 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D440 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>M</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$M$</span></mjx-container>이 공백으로 구분되어 주어진다.</p>

<p>그다음 줄부터 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D440 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>M</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$M$</span></mjx-container>개 줄에 걸쳐 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-msub><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D462 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub><mjx-mo class="mjx-n"><mjx-c class="mjx-c2C"></mjx-c></mjx-mo><mjx-msub space="2"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D463 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub><mjx-mo class="mjx-n"><mjx-c class="mjx-c2C"></mjx-c></mjx-mo><mjx-msub space="2"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D464 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><msub><mi>u</mi><mi>i</mi></msub><mo>,</mo><msub><mi>v</mi><mi>i</mi></msub><mo>,</mo><msub><mi>w</mi><mi>i</mi></msub></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$u_i, v_i, w_i$</span></mjx-container>가 공백으로 구분되어 주어진다. 이는 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>i</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$i$</span></mjx-container>번째 철도 구간이 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-msub><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D462 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub><mjx-mo class="mjx-n"><mjx-c class="mjx-c2C"></mjx-c></mjx-mo><mjx-msub space="2"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D463 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><msub><mi>u</mi><mi>i</mi></msub><mo>,</mo><msub><mi>v</mi><mi>i</mi></msub></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$u_i, v_i$</span></mjx-container>번 역을 양방향으로 연결하며, 이를 건설하여 운행할 경우 예상 수익은 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-msub><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D464 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><msub><mi>w</mi><mi>i</mi></msub></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$w_i$</span></mjx-container>임을 의미한다.</p>

### 출력 

 <p>첫 번째 줄에 규칙을 지키면서 철도를 만들 때, 예상 수익 합의 최댓값을 출력한다.</p>

