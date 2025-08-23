#include "ui_manager.h"
#include <iostream>

int main() {
  try {
    UIManager ui_manager;
    ui_manager.Run();
  } catch (const std::exception& e) {
    std::cerr << "오류가 발생했습니다: " << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "알 수 없는 오류가 발생했습니다." << std::endl;
    return 1;
  }
  
  return 0;
}
