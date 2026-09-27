# Happy Accidents

버그지만 예뻐서 남겨둠.

## 01. Accidental Pastel Eclipse

![Accidental Pastel Eclipse](./01_Accidental_Pastel_Eclipse.png)

- 생성일: 2026-09-27
- 해상도: 400 × 225
- 원본 포맷: P3 PPM
- 파일: [PNG](./01_Accidental_Pastel_Eclipse.png) / [PPM](./01_Accidental_Pastel_Eclipse.ppm)

안티 앨리어싱 구현 중, 계산 실수로 우연히 만들어진 이미지.

### 문제와 원인

**요약**

1. viewport 방향을 반대로 잡아서 화면이 상하로 뒤집혔다.
2. normal 색 계산에서 괄호를 잘못 쳐서 밝은 부분이 하얗게 날아갔다.

#### 1. 화면의 Y축 반전

```cpp
// 실수
auto viewportV = Vec3(0.0, viewportHeight, 0.0);

// 의도
auto viewportV = Vec3(0.0, -viewportHeight, 0.0);
```

이미지의 행 번호는 위에서 아래로 커지지만, 월드 좌표계에서는 위쪽이 +Y다.

그래서 `viewportV`의 Y 성분은 음수여야 하지만 Y 성분을 양수로 적어버려서 이미지가 위아래로 뒤집혔다.

#### 2. 법선 색상의 과노출

```cpp
// 실수
return (0.5 * (hitRecord.Normal) + Color(1.0, 1.0, 1.0));

// 의도
return 0.5 * ((hitRecord.Normal) + Color(1.0, 1.0, 1.0));
```

전체에 0.5를 곱해야 했는데, `normal`에만 곱해버렸다.

의도한 식은 법선 성분 `[-1, 1]`을 색상 `[0, 1]`로 옮긴다.

실제로 쓴 식은 `[0.5, 1.5]`를 만들었고, 1보다 큰 값이 `clamp`되면서 밝은 색이 하얗게 날아갔다.
