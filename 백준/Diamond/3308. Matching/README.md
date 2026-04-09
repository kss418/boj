# [Diamond III] Matching - 3308 

[문제 링크](https://www.acmicpc.net/problem/3308) 

### 성능 요약

메모리: 95372 KB, 시간: 680 ms

### 분류

자료 구조, 문자열, 세그먼트 트리, 집합과 맵, 값 / 좌표 압축, KMP

### 제출 일자

2026년 4월 9일 12:44:29

### 문제 설명

<p>As a part of a new advertising campaign, a big company in Gdynia wants to put its logo somewhere in the city. The company is going to spend the whole advertising budget for this year on the logo, so it has to be really huge. One of the managers decided to use whole buildings as parts of the logo.</p>

<p>The logo consists of n vertical stripes of different heights. The stripes are numbered from 1 to n from left to right. The logo is described by a permutation (s<sub>1</sub>, s<sub>2</sub>, . . . , s<sub>n</sub>) of numbers 1, 2, . . . , n. The stripe number s<sub>1</sub> is the shortest one, the stripe number s<sub>2</sub> is the second shortest etc., finally the stripe sn is the tallest one. The actual heights of the stripes do not really matter.</p>

<p>There are m buildings along the main street in Gdynia. To your surprise, the heights of the buildings are distinct. The problem is to find all positions where the logo matches the buildings.</p>

<p>Help the company and find all contiguous parts of the sequence of buildings which match the logo. A contiguous sequence of buildings matches the logo if the building number s<sub>1</sub> within this sequence is the shortest one, the building number s<sub>2</sub> is the second shortest, etc. For example a sequence of buildings of heights 5, 10, 4 matches a logo described by a permutation (3, 1, 2), since the building number 3 (of height 4) is the shortest one, the building number 1 is the second shortest and the building number 2 is the tallest.</p>

### 입력 

 <p>The first line of the standard input contains two integers n and m (2 ≤ n ≤ m ≤ 1 000 000). The second line contains n integers s<sub>i</sub>, forming a permutation of the numbers 1, 2, . . . , n. That is, 1 ≤ s<sub>i</sub> ≤ n and s<sub>i</sub> ≠ s<sub>j</sub> for i ≠ j. The third line contains m integers h<sub>i</sub> — the heights of the buildings (1 ≤ h<sub>i</sub> ≤ 10<sup>9</sup> for 1 ≤ i ≤ m). All the numbers hi are different. In each line the integers are separated by single spaces.</p>

### 출력 

 <p>The first line of the standard output should contain an integer k, the number of matches. The second line should contain k integers — 1-based indices of buildings which correspond to the stripe number 1 from the logo in a proper match. The numbers should be listed in an increasing order and separated by single spaces. If k = 0, your program should print an empty second line.</p>

