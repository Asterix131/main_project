# Skin Studio

Skin Studio — офлайн-редактор пресетов скинов с UI на **SDL3 + Dear ImGui**.

## Возможности (стартовый каркас)
- Боковая навигация: **Catalog / Presets / Settings**.
- Каталог с поиском и фильтрацией по редкости.
- Окно редактора выбранного скина:
  - `wear`
  - `StatTrak`
  - `seed`
  - `notes`
- Preview-панель с плейсхолдером изображения.
- JSON-сериализация пресетов в `config/presets.json` + автозагрузка при старте.

## Ограничения
Проект позиционируется как **офлайн-редактор**:
- без чит-функций,
- без инжекта,
- без работы с памятью процесса игры,
- только локальное редактирование пресетов.

## Сборка `.exe` (Windows, Release)

### 1) Требования
- CMake 3.24+
- Visual Studio 2022 (MSVC)
- Git
- Интернет для загрузки зависимостей (SDL3, Dear ImGui, nlohmann/json через FetchContent)

### 2) Конфигурация
```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
```

### 3) Сборка Release
```powershell
cmake --build build --config Release
```

### 4) Запуск
Итоговый файл:
- `build/Release/skin_studio.exe`

При post-build копируются каталоги:
- `assets/`
- `config/`

## Примечания
- При отсутствии `config/presets.json` приложение создаст файл с дефолтными пресетами.
- UI-каркас готов к расширению (дополнительные окна, загрузка реальных превью, пресет-менеджер и т.д.).

## Открытие в Visual Studio

### Вариант 1: через CMake Presets (генерация `.sln`)
```powershell
cmake --preset vs2022-release
```

После генерации откройте решение:
- `build/vs2022-release/skin_studio.sln`

### Вариант 2: Open Folder (без ручной генерации)
В Visual Studio 2022 выберите **File → Open → Folder...** и укажите корень проекта с `CMakeLists.txt`.
Visual Studio автоматически подхватит CMake-проект и выполнит конфигурацию без ручного запуска `cmake -S/-B`.
