#ifndef BUS_CARD_H_
#define BUS_CARD_H_

#include <string>
#include <chrono>
#include <vector>

class BusCard {
 public:
  // 생성자
  BusCard();
  explicit BusCard(const std::string& serial_number);
  
  // 기본 정보 접근자
  std::string GetSerialNumber() const;
  std::chrono::system_clock::time_point GetCreatedTime() const;
  bool IsActive() const;
  bool HasTaxApplied() const;
  
  // 상태 변경 메서드
  void SetActive(bool active);
  void SetTaxApplied(bool tax_applied);
  
  // 카드 정보 문자열 변환
  std::string ToString() const;
  
  // 시리얼 번호 생성 (정적 메서드)
  static std::string GenerateSerialNumber();

 private:
  std::string serial_number_;
  std::chrono::system_clock::time_point created_time_;
  bool is_active_;
  bool has_tax_applied_;
};

#endif  // BUS_CARD_H_
