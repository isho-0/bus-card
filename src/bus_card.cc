#include "bus_card.h"
#include <sstream>
#include <iomanip>
#include <random>
#include <chrono>

BusCard::BusCard() 
    : created_time_(std::chrono::system_clock::now()),
      is_active_(true),
      has_tax_applied_(false) {
  serial_number_ = GenerateSerialNumber();
}

BusCard::BusCard(const std::string& serial_number)
    : serial_number_(serial_number),
      created_time_(std::chrono::system_clock::now()),
      is_active_(true),
      has_tax_applied_(false) {
}

std::string BusCard::GetSerialNumber() const {
  return serial_number_;
}

std::chrono::system_clock::time_point BusCard::GetCreatedTime() const {
  return created_time_;
}

bool BusCard::IsActive() const {
  return is_active_;
}

bool BusCard::HasTaxApplied() const {
  return has_tax_applied_;
}

void BusCard::SetActive(bool active) {
  is_active_ = active;
}

void BusCard::SetTaxApplied(bool tax_applied) {
  has_tax_applied_ = tax_applied;
}

std::string BusCard::ToString() const {
  std::stringstream ss;
  auto time_t = std::chrono::system_clock::to_time_t(created_time_);
  auto tm = *std::localtime(&time_t);
  
  ss << "카드 번호: " << serial_number_ << "\n";
  ss << "생성 시간: " << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "\n";
  ss << "상태: " << (is_active_ ? "활성" : "비활성") << "\n";
  ss << "부가세: " << (has_tax_applied_ ? "적용됨" : "미적용");
  
  return ss.str();
}

std::string BusCard::GenerateSerialNumber() {
  auto now = std::chrono::system_clock::now();
  auto time_t = std::chrono::system_clock::to_time_t(now);
  auto tm = *std::localtime(&time_t);
  
  // 년월일시분초 (12자리)
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << (tm.tm_year % 100);  // 년 (2자리)
  ss << std::setfill('0') << std::setw(2) << (tm.tm_mon + 1);     // 월 (2자리)
  ss << std::setfill('0') << std::setw(2) << tm.tm_mday;          // 일 (2자리)
  ss << std::setfill('0') << std::setw(2) << tm.tm_hour;          // 시 (2자리)
  ss << std::setfill('0') << std::setw(2) << tm.tm_min;           // 분 (2자리)
  ss << std::setfill('0') << std::setw(2) << tm.tm_sec;           // 초 (2자리)
  
  // 3자리 난수 추가 (0-999)
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 999);
  ss << std::setfill('0') << std::setw(3) << dis(gen);
  
  return ss.str();
}
