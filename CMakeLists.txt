project(r-type)
cmake_minimum_required(VERSION 2.8.12)

if (MSVC)
else (MSVC)
  add_definitions("-fPIC")
endif (MSVC)

set(CONAN_DISABLE_CHECK_COMPILER True)

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

include(./build/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_INCLUDE_PATH})

set (BIN_SERVER r-type_server)
set (BIN_CLIENT r-type_client)

set (DEFAULT_ENEMY_SRC
  src/Entity/Entity.cpp
  src/Entity/SharedEntity.cpp
  src/Entity/Sprite/Sprite.cpp
  src/Entity/Sprite/Enemy/Enemy.cpp
  src/Entity/Sprite/Enemy/MovementEnemy.cpp
  src/Entity/Sprite/Enemy/Default/DefaultEnemy.cpp
  )

set (CYTRON_ENEMY_SRC
  src/Entity/Entity.cpp
  src/Entity/SharedEntity.cpp
  src/Entity/Sprite/Sprite.cpp
  src/Entity/Sprite/Enemy/Enemy.cpp
  src/Entity/Sprite/Enemy/MovementEnemy.cpp
  src/Entity/Sprite/Enemy/Cytron/Cytron.cpp
  )

set (BOB_ENEMY_SRC
  src/Entity/Entity.cpp
  src/Entity/SharedEntity.cpp
  src/Entity/Sprite/Sprite.cpp
  src/Entity/Sprite/Enemy/Enemy.cpp
  src/Entity/Sprite/Enemy/MovementEnemy.cpp
  src/Entity/Sprite/Enemy/Bob/Bob.cpp
  )
  
set (SORBET_ENEMY_SRC
  src/Entity/Entity.cpp
  src/Entity/SharedEntity.cpp
  src/Entity/Sprite/Sprite.cpp
  src/Entity/Sprite/Enemy/Enemy.cpp
  src/Entity/Sprite/Enemy/MovementEnemy.cpp
  src/Entity/Sprite/Enemy/Sorbet/Sorbet.cpp
  )

add_library(0_1_defaultEnemy SHARED ${DEFAULT_ENEMY_SRC})
add_library(0_2_cytronEnemy SHARED ${CYTRON_ENEMY_SRC})
add_library(0_3_bobEnemy SHARED ${BOB_ENEMY_SRC})
add_library(0_4_sorbetEnemy SHARED ${SORBET_ENEMY_SRC})

set (SRC_SERVER
  src/RTypeException/RTypeException.cpp
  src/serverMain.cpp
  src/Logger/Logger.cpp
  src/RTypeServer/RTypeServer.cpp
  src/Properties/RTypeProperties.cpp
  src/Properties/ServerProperties.cpp
  src/TcpConnection/TcpConnection.cpp
  src/UdpConnection/UdpConnection.cpp
  src/Utils/RTypeUtils.cpp
  src/Entity/Entity.cpp
  src/Entity/SharedEntity.cpp
  src/Entity/Sprite/Sprite.cpp
  src/Entity/Sprite/Enemy/MovementEnemy.cpp
  src/Entity/Sprite/Enemy/Enemy.cpp
  src/Utils/ServerUtils.cpp
  src/Parser/Parser.cpp
  src/DLLoader/DLLoader.cpp
  src/DLLoader/EnemyGenerator.cpp
  src/FileReader/FileReader.cpp
  src/DirectoriesReader/DirectoriesReader.cpp
  src/DirectoriesManager/DirectoriesManager.cpp
  src/ServerDataManagement/Client/Client.cpp
  src/ServerDataManagement/Lobby/Lobby.cpp
  )

set (SRC_CLIENT
  src/RTypeException/RTypeException.cpp
  src/clientMain.cpp
  src/Logger/Logger.cpp
  src/RTypeClient/RTypeClient.cpp
  src/TcpConnection/TcpConnection.cpp
  src/UdpConnection/UdpConnection.cpp
  src/DLLoader/DLLoader.cpp
  src/GraphicsEngine/SFMLEngine/SFMLEngine.cpp
  src/Utils/ClientUtils.cpp
  src/Utils/RTypeUtils.cpp
  src/Properties/ClientProperties.cpp
  src/Properties/RTypeProperties.cpp
  src/Parser/Parser.cpp
  src/Interfaces/InterfaceManager.cpp
  src/Interfaces/NetworkInterface.cpp
  src/Interfaces/Menu/Menu.cpp
  src/Interfaces/ServerConnection/ServerConnection.cpp
  src/Interfaces/Rooms/Rooms.cpp
  src/Interfaces/GameLobby/GameLobby.cpp
  src/Interfaces/CreateRoom/CreateRoom.cpp
  src/Interfaces/Option/Option.cpp
  src/Interfaces/Interface.cpp
  src/Interfaces/Game/Game.cpp
  src/Interfaces/MapCreator/MapCreator.cpp
  src/Interfaces/EndGame/EndGame.cpp
  src/UserEvent/KeyboardEvent/KeyboardEvent.cpp
  src/UserEvent/MouseEvent/MouseEvent.cpp
  src/UserEvent/ScreenEvent/ScreenEvent.cpp
  src/UserEvent/TextEvent/TextEvent.cpp
  src/UserEvent/UserEvent.cpp
  src/GameEngine/GameEngine.cpp
  src/Entity/Text/Text.cpp
  src/Entity/Text/LimitedText.cpp
  src/Entity/Text/AnimatedText.cpp
  src/Entity/Form/Form.cpp
  src/Entity/Sound/Sound.cpp
  src/Entity/Entity.cpp
  src/Entity/SharedEntity.cpp
  src/Entity/Sprite/Sprite.cpp
  src/Entity/Sprite/Directional.cpp
  src/Entity/Sprite/Player/Player.cpp
  src/Entity/Sprite/Enemy/Enemy.cpp
  src/Entity/Sprite/Enemy/MovementEnemy.cpp
  src/Entity/Sprite/Enemy/MovementEnemy.cpp
  src/Entity/Sprite/Projectile/Projectile.cpp
  )

if (MSVC)
else (MSVC)
	include(CTest)
	enable_testing(MAKE_DIRECTORY tests)
	add_subdirectory(tests)
endif (MSVC)

add_executable(${BIN_SERVER} ${SRC_SERVER})
add_executable(${BIN_CLIENT} ${SRC_CLIENT})

target_link_libraries(${BIN_SERVER} ${CONAN_LIBS})
target_link_libraries(${BIN_CLIENT} ${CONAN_LIBS})

if (MSVC)
	add_custom_command(TARGET ${BIN_CLIENT} POST_BUILD COMMAND cmd /c "start $(CMAKE_SOURCE_DIR)/binConfiguration.bat")
else (MSVC)
endif (MSVC)
