#ifndef TRANSIT_SYSTEM_H_
#define TRANSIT_SYSTEM_H_

#include <string>
#include <unordered_map>
#include <chrono>
#include "bus_card.h"

enum class TransportType {
  kBus,
  kSubway
};

enum class TripStatus {
  kNotTraveling,
  kOnBus,
  kOnSubway
};

struct TripRecord {
  std::string card_serial;
  TransportType transport_type;
  std::chrono::system_clock::time_point boarding_time;
  std::chrono::system_clock::time_point exit_time;
  bool is_transfer;
  double fare;
  bool tax_applied;
};

class TransitSystem {
 public:
  TransitSystem();
  
  // 카드 관리
  BusCard CreateCard();
  BusCard* GetCard(const std::string& serial_number);
  bool IsCardExists(const std::string& serial_number) const;
  
  // 탑승/하차
  bool BoardTransport(const std::string& serial_number, TransportType type);
  bool ExitTransport(const std::string& serial_number);
  
  // 환승 관련
  bool IsTransferEligible(const std::string& serial_number) const;
  void ProcessTransfer(const std::string& serial_number);
  
  // 상태 조회
  TripStatus GetCardStatus(const std::string& serial_number) const;
  std::vector<TripRecord> GetCardHistory(const std::string& serial_number) const;
  
  // 부가세 관리
  void ApplyTax(const std::string& serial_number);
  void RemoveTax(const std::string& serial_number);
  
  // 시스템 정보
  size_t GetTotalCards() const;
  size_t GetActiveTrips() const;

 private:
  std::unordered_map<std::string, BusCard> cards_;
  std::unordered_map<std::string, TripRecord> active_trips_;
  std::vector<TripRecord> trip_history_;
  
  // 환승 시간 제한 (30분)
  static constexpr int kTransferTimeLimitMinutes = 30;
  
  // 내부 헬퍼 메서드
  bool IsValidSerialNumber(const std::string& serial_number) const;
  void AddToHistory(const TripRecord& record);
};

#endif  // TRANSIT_SYSTEM_H_
