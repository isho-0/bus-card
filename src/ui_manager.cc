#include "ui_manager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include <iomanip>
#include <sstream>

UIManager::UIManager() : is_running_(true) {
}

void UIManager::Run() {
  ShowTitle();
  ShowLoading();
  
  while (is_running_) {
    ShowMainMenu();
    int choice = GetUserChoice(1, 3);
    
    switch (choice) {
      case 1:
        HandleAddCard();
        break;
      case 2:
        HandleOuting();
        break;
      case 3:
        is_running_ = false;
        ShowMessage("프로그램을 종료합니다.");
        break;
    }
  }
}

void UIManager::ShowTitle() {
  ClearScreen();
  DrawBox("🚌 버스 카드 관리 시스템 🚌");
  std::cout << "\n";
}

void UIManager::ShowLoading() {
  std::cout << "로딩 중";
  for (int i = 0; i < 3; ++i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << ".";
  }
  std::cout << "\n\n";
}

void UIManager::ShowMainMenu() {
  ClearScreen();
  DrawBox("🚌 버스 카드 관리 시스템 🚌");
  std::cout << "\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "|            메인 메뉴                |\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "| [1] 카드 추가                      |\n";
  std::cout << "| [2] 외출                           |\n";
  std::cout << "| [3] 종료                           |\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "\n선택하세요: ";
}

void UIManager::ShowTransportSelection() {
  std::cout << "\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "|        무엇을 통해 이동하시나요?     |\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "| [1] 버스                           |\n";
  std::cout << "| [2] 지하철                         |\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "\n선택하세요: ";
}

void UIManager::ShowBoardingMessage(TransportType type) {
  std::string transport_name = (type == TransportType::kBus) ? "버스" : "지하철";
  
  std::cout << "\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "|           탑승 시간                 |\n";
  std::cout << "+-------------------------------------+\n";
  
  auto now = std::chrono::system_clock::now();
  auto time_t = std::chrono::system_clock::to_time_t(now);
  auto tm = *std::localtime(&time_t);
  
  std::cout << "| " << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " |\n";
  std::cout << "+-------------------------------------+\n";
  
  std::cout << "\n";
  std::cout << "🚌 " << transport_name << " 탑승중...\n";
  
  if (type == TransportType::kBus) {
    std::cout << "🔔 하차 시, 벨을 눌러주세요!\n";
  } else {
    std::cout << "🚇 하차 시, 문이 열리면 내려주세요!\n";
  }
}

void UIManager::ShowExitMessage() {
  std::cout << "\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "|           하차 완료                 |\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "\n";
}

void UIManager::ShowFareInfo(double fare, bool is_transfer) {
  std::cout << "\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "|           요금 정보                 |\n";
  std::cout << "+-------------------------------------+\n";
  
  if (is_transfer) {
    std::cout << "| 🎫 환승 할인이 적용되었습니다!      |\n";
  }
  
  std::cout << "| 💰 요금: " << std::fixed << std::setprecision(0) 
            << std::setw(8) << fare << "원        |\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "\n";
}

void UIManager::ShowTransferOptions() {
  std::cout << "\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "|           다음 이동 방법            |\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "| [1] 버스                           |\n";
  std::cout << "| [2] 지하철                         |\n";
  std::cout << "| [3] 목적지 도착                    |\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "\n선택하세요: ";
}

void UIManager::ShowTaxAppliedMessage() {
  std::cout << "\n";
  std::cout << "⚠️  부가세가 적용되었습니다!\n";
  std::cout << "\n";
}

void UIManager::ShowCardSelectionMenu() {
  std::cout << "\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "|           카드 선택                 |\n";
  std::cout << "+-------------------------------------+\n";
  
  auto card_list = transit_system_.GetCardList();
  
  if (card_list.empty()) {
    std::cout << "| ❌ 등록된 카드가 없습니다!           |\n";
    std::cout << "|    먼저 카드를 추가해주세요.        |\n";
    std::cout << "+-------------------------------------+\n";
    return;
  }
  
  for (const auto& card_pair : card_list) {
    std::string index = card_pair.first;
    std::string serial = card_pair.second;
    
    std::cout << "| [" << std::left << std::setw(2) << index << "] " 
              << std::left << std::setw(25) << serial << " |\n";
  }
  
  std::cout << "+-------------------------------------+\n";
  std::cout << "\n사용할 카드 번호를 선택하세요: ";
}

std::string UIManager::SelectCardByNumber() {
  auto card_list = transit_system_.GetCardList();
  
  if (card_list.empty()) {
    return "";
  }
  
  int choice = GetUserChoice(1, static_cast<int>(card_list.size()));
  std::string selected_serial = transit_system_.GetCardByIndex(choice);
  
  if (!selected_serial.empty()) {
    // 선택된 카드 정보 표시
    BusCard* selected_card = transit_system_.GetCard(selected_serial);
    if (selected_card) {
      std::cout << "\n✅ 선택된 카드: " << selected_serial << "\n";
    }
  }
  
  return selected_serial;
}

int UIManager::GetUserChoice(int min, int max) {
  int choice;
  while (true) {
    if (std::cin >> choice) {
      if (choice >= min && choice <= max) {
        return choice;
      }
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "올바른 선택지를 입력해주세요 (" << min << "-" << max << "): ";
  }
}

std::string UIManager::GetCardSerialNumber() {
  std::string serial;
  std::cout << "카드 시리얼 번호를 입력하세요: ";
  std::cin >> serial;
  return serial;
}

TransportType UIManager::GetTransportType() {
  int choice = GetUserChoice(1, 2);
  return (choice == 1) ? TransportType::kBus : TransportType::kSubway;
}

void UIManager::ShowMessage(const std::string& message) {
  std::cout << message << "\n";
}

void UIManager::ShowSuccessMessage(const std::string& message) {
  std::cout << "✅ " << message << "\n";
}

void UIManager::ShowErrorMessage(const std::string& message) {
  std::cout << "❌ " << message << "\n";
}

void UIManager::ShowCardInfo(const BusCard& card) {
  std::cout << "\n";
  std::cout << "+-------------------------------------+\n";
  std::cout << "|           카드 정보                 |\n";
  std::cout << "+-------------------------------------+\n";
  
  std::string info = card.ToString();
  std::istringstream iss(info);
  std::string line;
  
  while (std::getline(iss, line)) {
    std::cout << "| " << std::left << std::setw(35) << line << " |\n";
  }
  
  std::cout << "+-------------------------------------+\n";
  std::cout << "\n";
}

void UIManager::ClearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void UIManager::WaitForEnter() {
  std::cout << "\n계속하려면 Enter를 누르세요...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
}

void UIManager::HandleAddCard() {
  BusCard new_card = transit_system_.CreateCard();
  
  ShowSuccessMessage("카드가 추가되었습니다!");
  std::cout << "시리얼 번호: " << new_card.GetSerialNumber() << "\n";
  std::cout << "\n⚠️  카드 번호를 기억해주세요!\n";
  
  WaitForEnter();
}

void UIManager::HandleOuting() {
  ShowTransportSelection();
  TransportType type = GetTransportType();
  
  // 카드 선택 메뉴 표시
  ShowCardSelectionMenu();
  std::string serial = SelectCardByNumber();
  
  if (serial.empty()) {
    ShowErrorMessage("카드 선택에 실패했습니다!");
    WaitForEnter();
    return;
  }
  
  // 부가세 적용 여부 확인
  BusCard* card = transit_system_.GetCard(serial);
  if (card && card->HasTaxApplied()) {
    ShowTaxAppliedMessage();
  }
  
  if (transit_system_.BoardTransport(serial, type)) {
    ShowBoardingMessage(type);
    
    // 하차 시 사용자 입력 대기 (교통수단에 따라 다른 메시지)
    if (type == TransportType::kBus) {
      std::cout << "\n🔔 하차벨을 누르고 Enter를 눌러주세요...";
    } else {
      std::cout << "\n🚇 하차하시려면 Enter를 눌러주세요...";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    
    // 하차 처리
    ShowExitMessage();
    transit_system_.ExitTransport(serial);
    
    // 요금 정보 표시
    auto transfer_info = transit_system_.GetTransferInfo(serial);
    ShowFareInfo(transfer_info.second, transfer_info.first);
    
    // 환승 옵션 표시
    ShowTransferOptions();
    int choice = GetUserChoice(1, 3);
    
    if (choice == 3) {
      // 목적지 도착
      ShowSuccessMessage("목적지에 도착했습니다!");
    } else {
      // 환승 처리
      TransportType transfer_type = (choice == 1) ? TransportType::kBus : TransportType::kSubway;
      
      if (transit_system_.IsTransferEligible(serial)) {
        ShowSuccessMessage("환승이 적용되었습니다!");
      }
      
      if (transit_system_.BoardTransport(serial, transfer_type)) {
        ShowBoardingMessage(transfer_type);
        
        // 두 번째 하차 시에도 사용자 입력 대기 (교통수단에 따라 다른 메시지)
        if (transfer_type == TransportType::kBus) {
          std::cout << "\n🔔 하차벨을 누르고 Enter를 눌러주세요...";
        } else {
          std::cout << "\n🚇 하차하시려면 Enter를 눌러주세요...";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        
        ShowExitMessage();
        transit_system_.ExitTransport(serial);
        
        // 최종 요금 정보 표시
        auto final_transfer_info = transit_system_.GetTransferInfo(serial);
        ShowFareInfo(final_transfer_info.second, final_transfer_info.first);
        
        ShowSuccessMessage("최종 목적지에 도착했습니다!");
      }
    }
  } else {
    ShowErrorMessage("탑승 처리에 실패했습니다!");
  }
  
  WaitForEnter();
}

void UIManager::DrawBox(const std::string& text) {
  int width = 40;
  std::cout << "+";
  DrawLine('-', width - 2);
  std::cout << "+\n";
  
  std::cout << "| " << std::left << std::setw(width - 4) << text << " |\n";
  
  std::cout << "+";
  DrawLine('-', width - 2);
  std::cout << "+\n";
}

void UIManager::DrawLine(char character, int length) {
  for (int i = 0; i < length; ++i) {
    std::cout << character;
  }
}
