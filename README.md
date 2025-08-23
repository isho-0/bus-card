# Bus Card Project

C++로 개발된 미니 프로젝트입니다.

## 프로젝트 구조

```
.
├── CMakeLists.txt          # 메인 CMake 설정 파일
├── src/                    # 소스 코드 디렉토리
│   ├── CMakeLists.txt     # src 디렉토리 CMake 설정
│   └── main.cpp           # 메인 소스 파일
├── build/                  # 빌드 출력 디렉토리
└── README.md              # 프로젝트 설명서
```

## 빌드 방법

### 1. 빌드 디렉토리 생성 및 이동
```bash
mkdir build
cd build
```

### 2. CMake 설정
```bash
cmake ..
```

### 3. 빌드
```bash
make
```

### 4. 실행
```bash
./bus-card
```

## 요구사항

- CMake 3.16 이상
- C++17 호환 컴파일러 (GCC, Clang, MSVC 등)

## 개발 환경 설정

프로젝트는 다음 도구들을 지원합니다:
- CMake
- 다양한 C++ 컴파일러
- IDE 통합 (VS Code, CLion 등)

