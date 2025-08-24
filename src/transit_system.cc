#include "transit_system.h"
#include <algorithm>
#include <chrono>
#include "fare_calculator.h"

TransitSystem::TransitSystem() {
}

BusCard TransitSystem::CreateCard() {
  BusCard new_card;
  cards_[new_card.GetSerialNumber()] = new_card;
  return new_card;
}

BusCard* TransitSystem::GetCard(const std::string& serial_number) {
  auto it = cards_.find(serial_number);
  if (it != cards_.end()) {
    return &(it->second);
  }
  return nullptr;
}

bool TransitSystem::IsCardExists(const std::string& serial_number) const {
  return cards_.find(serial_number) != cards_.end();
}

bool TransitSystem::BoardTransport(const std::string& serial_number, TransportType type) {
  if (!IsCardExists(serial_number)) {
    return false;
  }
  
  // 이미 탑승 중인지 확인
  if (active_trips_.find(serial_number) != active_trips_.end()) {
    return false;
  }
  
  // 부가세 적용 여부 확인
  BusCard* card = GetCard(serial_number);
  bool tax_applied = card->HasTaxApplied();
  
  // 환승 가능 여부 확인
  bool is_transfer = IsTransferEligible(serial_number);
  
  // 새로운 여행 기록 생성
  TripRecord record;
  record.card_serial = serial_number;
  record.transport_type = type;
  record.boarding_time = std::chrono::system_clock::now();
  record.is_transfer = is_transfer;
  record.fare = 0.0;  // 하차 시 계산
  record.tax_applied = tax_applied;
  
  active_trips_[serial_number] = record;
  
  return true;
}

bool TransitSystem::ExitTransport(const std::string& serial_number) {
  auto it = active_trips_.find(serial_number);
  if (it == active_trips_.end()) {
    return false;
  }
  
  TripRecord& record = it->second;
  record.exit_time = std::chrono::system_clock::now();
  
  // 요금 계산
  FareCalculator calculator;
  record.fare = calculator.CalculateFinalFare(
      record.transport_type, 
      record.is_transfer,
      0.0  // 거리는 기본값으로 설정
  );
  
  // 여행 기록을 히스토리에 추가
  AddToHistory(record);
  
  // 활성 여행에서 제거
  active_trips_.erase(it);
  
  return true;
}

bool TransitSystem::IsTransferEligible(const std::string& serial_number) const {
  // 최근 하차 기록이 있는지 확인
  for (auto it = trip_history_.rbegin(); it != trip_history_.rend(); ++it) {
    if (it->card_serial == serial_number) {
      auto now = std::chrono::system_clock::now();
      auto time_diff = std::chrono::duration_cast<std::chrono::minutes>(
          now - it->exit_time);
      
      // 30분 내에 재탑승 시 환승 가능
      return time_diff.count() <= kTransferTimeLimitMinutes;
    }
  }
  return false;
}

void TransitSystem::ProcessTransfer(const std::string& serial_number) {
  // 환승 처리 로직은 이미 BoardTransport에서 처리됨
  (void)serial_number;
}

TripStatus TransitSystem::GetCardStatus(const std::string& serial_number) const {
  auto it = active_trips_.find(serial_number);
  if (it == active_trips_.end()) {
    return TripStatus::kNotTraveling;
  }
  
  switch (it->second.transport_type) {
    case TransportType::kBus:
      return TripStatus::kOnBus;
    case TransportType::kSubway:
      return TripStatus::kOnSubway;
    default:
      return TripStatus::kNotTraveling;
  }
}

std::vector<TripRecord> TransitSystem::GetCardHistory(const std::string& serial_number) const {
  std::vector<TripRecord> history;
  
  for (const auto& record : trip_history_) {
    if (record.card_serial == serial_number) {
      history.push_back(record);
    }
  }
  
  return history;
}

void TransitSystem::ApplyTax(const std::string& serial_number) {
  BusCard* card = GetCard(serial_number);
  if (card) {
    card->SetTaxApplied(true);
  }
}

void TransitSystem::RemoveTax(const std::string& serial_number) {
  BusCard* card = GetCard(serial_number);
  if (card) {
    card->SetTaxApplied(false);
  }
}

size_t TransitSystem::GetTotalCards() const {
  return cards_.size();
}

size_t TransitSystem::GetActiveTrips() const {
  return active_trips_.size();
}

bool TransitSystem::IsValidSerialNumber(const std::string& serial_number) const {
  // 15자리 시리얼 번호 검증
  return serial_number.length() == 15 && 
         std::all_of(serial_number.begin(), serial_number.end(), ::isdigit);
}

void TransitSystem::AddToHistory(const TripRecord& record) {
  trip_history_.push_back(record);
}

// 새로운 메서드: 현재 활성 여행 정보 조회
TripRecord* TransitSystem::GetActiveTrip(const std::string& serial_number) {
  auto it = active_trips_.find(serial_number);
  if (it != active_trips_.end()) {
    return &(it->second);
  }
  return nullptr;
}

// 새로운 메서드: 환승 가능 여부와 함께 요금 정보 반환
std::pair<bool, double> TransitSystem::GetTransferInfo(const std::string& serial_number) const {
  bool is_transfer = IsTransferEligible(serial_number);
  
  FareCalculator calculator;
  double fare = calculator.CalculateFinalFare(
      TransportType::kBus,  // 기본값으로 버스 사용
      is_transfer,
      0.0
  );
  
  return {is_transfer, fare};
}
