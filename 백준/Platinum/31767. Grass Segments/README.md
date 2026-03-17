# [Platinum I] Grass Segments - 31767 

[문제 링크](https://www.acmicpc.net/problem/31767) 

### 성능 요약

메모리: 46336 KB, 시간: 756 ms

### 분류

자료 구조, 정렬, 세그먼트 트리, 스위핑, 오프라인 쿼리, 값 / 좌표 압축

### 제출 일자

2026년 3월 17일 14:01:17

### 문제 설명

<p>Bessie is planting some grass on the positive real line. She has $N$ ($2\le N\le 2\cdot 10^5$) different cultivars of grass, and will plant the $i$th cultivar on the interval $[\ell_i, r_i]$ ($0 < \ell_i < r_i \leq 10^9$).</p>

<p>In addition, cultivar $i$ grows better when there is some cultivar $j$ ($j\neq i$) such that cultivar $j$ and cultivar $i$ overlap with length at least $k_i$ ($0 < k_i \leq r_i - \ell_i$). Bessie wants to evaluate all of her cultivars. For each $i$, compute the number of $j\neq i$ such that $j$ and $i$ overlap with length at least $k_i$.</p>

### 입력 

 <p>The first line contains $N$.</p>

<p>The next $N$ lines each contain three space-separated integers $\ell_i$, $r_i$, and $k_i$.</p>

### 출력 

 <p>The answers for all cultivars on separate lines.</p>

