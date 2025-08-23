# 🚌 C++ 버스카드 관리 시스템

![Language](https://img.shields.io/badge/language-C++17-blue?logo=c%2B%2B)
![Build](https://img.shields.io/badge/build-CMake-green?logo=cmake)
![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux%20%7C%20Windows-orange?logo=apple)
![Status](https://img.shields.io/badge/status-development%20in%20progress-yellow)

> "C++17로 만든 버스카드 시리얼 번호 기반 탑승/하차/환승/부가세 관리 시스템"  
> 고유 시리얼 번호를 가진 버스카드의 전 과정을 추적하고 관리하는 미니 프로젝트입니다.

---

## 🧭 개요

이 프로젝트는 **C++17**을 사용하여 개발된 버스카드 관리 시스템입니다.  
각 버스카드는 고유한 시리얼 번호를 가지며, 탑승부터 하차까지의 전 과정을 추적합니다.  
환승 시스템과 부가세 계산을 포함한 완전한 버스카드 생태계를 구현하여,  
대중교통 시스템의 핵심 기능을 미니 프로젝트로 체험할 수 있습니다.

---

## ⚙️ 환경

- **언어**: C++17
- **빌드 시스템**: CMake 3.16+
- **지원 플랫폼**: macOS, Linux, Windows
- **컴파일러**: GCC, Clang, MSVC
- **코드 스타일**: Google C++ Style Guide 준수
- **버전 관리**: Git & GitHub

---

## 🗂️ 프로젝트 구조

<pre>
bus-card/
├── CMakeLists.txt          # 메인 CMake 설정
├── src/                    # 소스 코드
│   ├── CMakeLists.txt      # 소스 빌드 설정
│   ├── main.cpp            # 메인 함수
│   ├── bus_card.hpp        # 버스카드 클래스
│   ├── bus_card.cpp        # 버스카드 구현
│   ├── transit_system.hpp  # 대중교통 시스템 클래스
│   ├── transit_system.cpp  # 대중교통 시스템 구현
│   ├── fare_calculator.hpp # 요금 계산기 클래스
│   ├── fare_calculator.cpp # 요금 계산기 구현
│   ├── serial_manager.hpp  # 시리얼 번호 관리 클래스
│   └── serial_manager.cpp  # 시리얼 번호 관리 구현
├── build/                  # 빌드 출력 디렉토리
├── .gitignore             # Git 무시 파일
├── .clang-format          # 코드 포맷팅 설정 (Google 스타일)
└── README.md              # 프로젝트 문서
</pre>

---

## 🚀 주요 기능

### 🔥 **버스카드 관리**
- **고유 시리얼 번호**: 각 카드마다 유일한 식별자 부여
- **카드 상태 추적**: 활성/비활성, 잔액, 사용 이력
- **보안 기능**: 시리얼 번호 검증 및 무결성 확인

### 🚌 **탑승/하차 시스템**
- **탑승 처리**: 시리얼 번호 인식 및 탑승 시간 기록
- **하차 처리**: 하차 시간 기록 및 요금 계산
- **실시간 추적**: 현재 탑승 중인 카드들의 상태 모니터링

### 🔄 **환승 시스템**
- **환승 인식**: 일정 시간 내 하차 후 재탑승 시 환승 처리
- **환승 할인**: 환승 조건 충족 시 할인 요금 적용
- **환승 이력**: 환승 패턴 분석 및 통계

### 💰 **요금 및 부가세**
- **기본 요금**: 거리별 기본 요금 계산
- **부가세 계산**: VAT 및 기타 세금 적용
- **할인 정책**: 환승, 학생, 노약자 등 할인 적용
- **영수증 생성**: 상세한 요금 내역 및 부가세 정보

### 📊 **데이터 관리**
- **사용 이력**: 모든 탑승/하차 기록 저장
- **통계 분석**: 일별/월별 이용 통계
- **데이터 내보내기**: CSV, JSON 등 다양한 형식 지원

---

## 📦 빌드 및 실행

### **1. 저장소 클론**
```bash
git clone <repository-url>
cd bus-card
```

### **2. 빌드**
```bash
mkdir build && cd build
cmake ..
make
```

### **3. 실행**
```bash
./src/bus-card
```

---

## 💻 사용법

### **기본 사용**
```cpp
#include "transit_system.hpp"
#include "bus_card.hpp"

int main() {
    TransitSystem system;
    
    // 버스카드 생성 (고유 시리얼 번호 자동 생성)
    BusCard card = system.createCard();
    
    // 탑승 처리
    system.boardBus(card.getSerialNumber());
    
    // ... 버스 이동 ...
    
    // 하차 처리
    system.exitBus(card.getSerialNumber());
    
    return 0;
}
```

### **환승 처리**
```cpp
// 첫 번째 버스에서 하차
system.exitBus(card.getSerialNumber());

// 30분 내에 다른 버스 탑승 (환승)
if (system.isTransferEligible(card.getSerialNumber())) {
    system.boardBus(card.getSerialNumber(), true); // 환승 플래그
}
```

### **요금 계산**
```cpp
FareCalculator calculator;
double fare = calculator.calculateFare(
    distance,           // 이동 거리
    isTransfer,         // 환승 여부
    cardType           // 카드 타입 (일반/학생/노약자)
);

double totalWithTax = calculator.addTax(fare); // 부가세 포함
```

---

## 🔧 구현 방식

### **시리얼 번호 시스템**
- **UUID 기반**: 고유성 보장을 위한 UUID v4 사용
- **체크섬**: 시리얼 번호 무결성 검증
- **데이터베이스**: 중복 방지를 위한 시리얼 번호 관리

### **탑승/하차 추적**
- **타임스탬프**: 정확한 시간 기록을 위한 Unix timestamp
- **GPS 연동**: 향후 실제 위치 기반 요금 계산 지원
- **실시간 업데이트**: WebSocket을 통한 실시간 상태 동기화

### **환승 로직**
- **시간 기반**: 하차 후 일정 시간 내 재탑승 시 환승 인식
- **라인 기반**: 서로 다른 버스 노선 간 환승 처리
- **할인 정책**: 환승 시 할인율 및 최대 할인 금액 설정

### **부가세 계산**
- **VAT 적용**: 기본 요금에 대한 부가가치세 계산
- **지역별 세율**: 지역에 따른 차등 세율 적용
- **면세 대상**: 학생, 노약자 등 특정 그룹에 대한 면세 처리

---

## 🧪 테스트

프로젝트는 포괄적인 테스트 스위트를 포함합니다:

- **BusCard 테스트**: 카드 생성 및 관리 기능 검증
- **TransitSystem 테스트**: 탑승/하차 시스템 검증
- **FareCalculator 테스트**: 요금 계산 및 부가세 적용 검증
- **SerialManager 테스트**: 시리얼 번호 관리 시스템 검증

---

## 📊 성능 및 확장성

### **현재 구현**
- **단일 스레드**: 기본적인 동기 처리
- **메모리 기반**: 간단한 인메모리 데이터 저장
- **기본 기능**: 핵심 탑승/하차 및 요금 계산

### **향후 개선 계획**
- [ ] **멀티스레딩**: 동시 다발적 요청 처리
- [ ] **데이터베이스**: SQLite/PostgreSQL 연동
- [ ] **네트워크**: TCP/UDP를 통한 실시간 통신
- [ ] **웹 인터페이스**: REST API 및 웹 대시보드
- [ ] **모바일 앱**: iOS/Android 앱 연동

---

## 🌊 Commit Convention (커밋 규칙)

| 유형 | 설명 |
|------|------|
| `feat` | 새로운 기능 추가 |
| `fix` | 버그 수정 |
| `docs` | 문서 수정 |
| `refactor` | 코드 리팩토링 |
| `test` | 테스트 추가 또는 수정 |
| `perf` | 성능 개선 |
| `build` | 빌드 시스템 또는 외부 종속성 변경 |

**예시**:
```bash
git commit -m "feat: 버스카드 시리얼 번호 자동 생성 기능 추가"
git commit -m "fix: 환승 할인 계산 오류 수정"
git commit -m "docs: README 업데이트 및 사용법 추가"
```

---

## 🤝 기여하기

버그 리포트, 기능 요청, 풀 리퀘스트를 환영합니다!

### **기여 방법**
1. 이슈 생성 또는 기존 이슈 확인
2. 포크 후 기능 브랜치 생성
3. 코드 작성 및 테스트 (Google C++ Style Guide 준수)
4. 풀 리퀘스트 제출

### **개발 환경 설정**
```bash
# 개발 의존성 설치
brew install cmake  # macOS
sudo apt install cmake  # Ubuntu/Debian

# 코드 포맷팅 (Google 스타일)
clang-format -i src/*.cpp src/*.hpp
```

---

## 📄 라이선스

이 프로젝트는 **MIT 라이선스** 하에 배포됩니다.

---

## 🙋‍♂️ About Me

- **GitHub**: [@isho-0](https://github.com/isho-0)
- **프로젝트**: C++ 버스카드 관리 시스템
- **목표**: 대중교통 시스템의 핵심 기능을 C++로 구현

---

**Made with ❤️ by isho-0.**  
*버스카드 하나로 연결되는 스마트한 대중교통 시스템을 구현합니다.*

