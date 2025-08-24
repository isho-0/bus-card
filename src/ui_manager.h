#ifndef UI_MANAGER_H_
#define UI_MANAGER_H_

#include <string>
#include "transit_system.h"
#include "fare_calculator.h"

class UIManager {
 public:
  UIManager();
  
  // 메인 UI 실행
  void Run();
  
  // 화면 표시 메서드
  void ShowTitle();
  void ShowLoading();
  void ShowMainMenu();
  void ShowTransportSelection();
  void ShowBoardingMessage(TransportType type);
  void ShowExitMessage();
  void ShowFareInfo(double fare, bool is_transfer);
  void ShowTransferOptions();
  void ShowTaxAppliedMessage();
  
  // 카드 선택 관련
  void ShowCardSelectionMenu();
  std::string SelectCardByNumber();
  
  // 사용자 입력 처리
  int GetUserChoice(int min, int max);
  std::string GetCardSerialNumber();
  TransportType GetTransportType();
  
  // 메시지 표시
  void ShowMessage(const std::string& message);
  void ShowSuccessMessage(const std::string& message);
  void ShowErrorMessage(const std::string& message);
  void ShowCardInfo(const BusCard& card);
  
  // 화면 정리
  void ClearScreen();
  void WaitForEnter();

 private:
  TransitSystem transit_system_;
  FareCalculator fare_calculator_;
  
  // UI 상태
  bool is_running_;
  
  // 내부 헬퍼 메서드
  void HandleAddCard();
  void HandleOuting();
  void HandleTransport(TransportType type);
  void HandleExit();
  void HandleTransfer();
  
  // 화면 그리기 헬퍼
  void DrawBox(const std::string& text);
  void DrawLine(char character, int length);
};

#endif  // UI_MANAGER_H_
