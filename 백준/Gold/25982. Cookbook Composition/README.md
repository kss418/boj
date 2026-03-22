# [Gold IV] Cookbook Composition - 25982 

[문제 링크](https://www.acmicpc.net/problem/25982) 

### 성능 요약

메모리: 2260 KB, 시간: 152 ms

### 분류

다이나믹 프로그래밍, 자료 구조, 그래프 이론, 집합과 맵, 해시를 사용한 집합과 맵, 방향 비순환 그래프, 위상 정렬

### 제출 일자

2026년 3월 22일 17:57:00

### 문제 설명

<p>The world-famous chef Gordon Oliver is composing a new cookbook called "Becoming A Perfect Chef". He has a list of recipes that he wants to publish in the cookbook. Each recipe is in the form of a list of steps, where every step might depend on some previous steps (meaning a step cannot be started until all its dependencies have finished), and expected time per step.</p>

<p>Gordon knows that, as an expert chef, he can multitask and do as many tasks simultaneously as needed. Meanwhile, a beginner can do one task at a time, so they need to execute them sequentially. He would like to order the recipes for the cookbook by accessibility, where the lowest $\frac{\text{beginner time}}{\text{expert time}}$ ratio recipes come first.</p>

<p>As an example, consider the first sample case. For the oven dish, an expert chef like Gordon Oliver can prepare the tomatoes, eggplants, and sauce all at the same time (with the sauce taking the longest: $5$ time), and followed by arranging ($1$) and baking ($30$) the dish, this takes $5+1+30=36$ time. On the other hand, a beginner needs $2+2+5+1+30=40$ time to make the oven dish. This makes the accessibility ratio of the oven dish $40/36\approx 1.11$. The accessibility ratio of the ice cream is $1$ (because beginner and expert chefs both require $5+5+5+240=255$ time to prepare it), so it comes before the oven dish in the cookbook.</p>

### 입력 

 <p>The input consists of:</p>

<ul>
	<li>One line with an integer $n$ ($2\leq n\leq 500$), the number of recipes.</li>
	<li>Then, for every recipe:
	<ul>
		<li>One line with the name of the recipe and an integer $s$ ($1\leq s\leq 50$), the number of steps in the recipe.</li>
		<li>$s$ lines, one for every step in the recipe, with the step name, an integer $t$ ($1\leq t\leq 10^6$), the step duration, an integer $d$ ($0\leq d\leq 49$), the number of dependencies, followed by a list of step names that this step depends on. A step only appears once all the steps that it depends on have been listed.</li>
	</ul>
	</li>
</ul>

<p>The recipe and step names consist of at most $10$ English lowercase letters (<code>a-z</code>).</p>

<p>The recipe names are unique and the step names are unique per recipe.</p>

### 출력 

 <p>Output the names of the recipes in the cookbook, ordered by accessibility.</p>

<p>If there are multiple valid solutions, you may output any one of them.</p>

