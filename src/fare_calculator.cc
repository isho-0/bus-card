#include "fare_calculator.h"

FareCalculator::FareCalculator()
    : transfer_discount_rate_(0.2),  // 20% 할인
      tax_rate_(0.1) {               // 10% 부가세
}

double FareCalculator::CalculateBaseFare(TransportType transport_type, double distance) const {
  double base_fare = 0.0;
  
  switch (transport_type) {
    case TransportType::kBus:
      base_fare = kBaseBusFare;
      break;
    case TransportType::kSubway:
      base_fare = kBaseSubwayFare;
      break;
  }
  
  // 거리별 추가 요금 (1km당 100원)
  if (distance > 0.0) {
    base_fare += distance * kDistanceRate;
  }
  
  return base_fare;
}

double FareCalculator::ApplyTransferDiscount(double base_fare, bool is_transfer) const {
  if (is_transfer) {
    return base_fare * (1.0 - transfer_discount_rate_);
  }
  return base_fare;
}

double FareCalculator::CalculateTax(double fare) const {
  return fare * tax_rate_;
}

double FareCalculator::AddTax(double fare) const {
  return fare + CalculateTax(fare);
}

double FareCalculator::CalculateFinalFare(TransportType transport_type, 
                                        bool is_transfer, 
                                        double distance) const {
  double base_fare = CalculateBaseFare(transport_type, distance);
  double discounted_fare = ApplyTransferDiscount(base_fare, is_transfer);
  return discounted_fare;
}

void FareCalculator::SetTransferDiscountRate(double rate) {
  if (rate >= 0.0 && rate <= 1.0) {
    transfer_discount_rate_ = rate;
  }
}

void FareCalculator::SetTaxRate(double rate) {
  if (rate >= 0.0 && rate <= 1.0) {
    tax_rate_ = rate;
  }
}

double FareCalculator::GetTransferDiscountRate() const {
  return transfer_discount_rate_;
}

double FareCalculator::GetTaxRate() const {
  return tax_rate_;
}
