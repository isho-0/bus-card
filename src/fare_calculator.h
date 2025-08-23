#ifndef FARE_CALCULATOR_H_
#define FARE_CALCULATOR_H_

#include "transit_system.h"

class FareCalculator {
 public:
  FareCalculator();
  
  // 기본 요금 계산
  double CalculateBaseFare(TransportType transport_type, double distance = 0.0) const;
  
  // 환승 할인 적용
  double ApplyTransferDiscount(double base_fare, bool is_transfer) const;
  
  // 부가세 계산
  double CalculateTax(double fare) const;
  double AddTax(double fare) const;
  
  // 최종 요금 계산
  double CalculateFinalFare(TransportType transport_type, 
                           bool is_transfer = false, 
                           double distance = 0.0) const;
  
  // 할인 정책 설정
  void SetTransferDiscountRate(double rate);
  void SetTaxRate(double rate);
  
  // 현재 설정된 요율 조회
  double GetTransferDiscountRate() const;
  double GetTaxRate() const;

 private:
  // 기본 요금 (원)
  static constexpr double kBaseBusFare = 1300.0;
  static constexpr double kBaseSubwayFare = 1250.0;
  
  // 환승 할인율 (20%)
  double transfer_discount_rate_;
  
  // 부가세율 (10%)
  double tax_rate_;
  
  // 거리별 추가 요금 (km당)
  static constexpr double kDistanceRate = 100.0;
};

#endif  // FARE_CALCULATOR_H_
