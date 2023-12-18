project(SudokuLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h
        pch.h
        SudokuView.cpp
        SudokuView.h
        SudokuGame.cpp
        SudokuGame.h
        Item.cpp
        Item.h
        ids.h
        Scoreboard.cpp
        Scoreboard.h
        Container.h
        Sparty.h
        Xray.h
        Xray.cpp
        Container.cpp
        Number.cpp
        Number.h
        Sparty.cpp
        Declaration.cpp
        Declaration.h
        Digit.cpp
        Digit.h
        Given.cpp
        Given.h
        Background.cpp
        Background.h
        LevelEndMessage.cpp
        LevelEndMessage.h
        Declaration.cpp
        Declaration.h
        NumberDeclaration.cpp
        NumberDeclaration.h
        ContainerDeclaration.cpp
        ContainerDeclaration.h
        SpartyDeclaration.cpp
        SpartyDeclaration.h
        XRayDeclaration.cpp
        XRayDeclaration.h
        BackgroundDeclaration.cpp
        BackgroundDeclaration.h
        SingleImageItem.cpp
        SingleImageItem.h
        SingleImageDeclaration.cpp
        SingleImageDeclaration.h
        Level.cpp
        Level.h
        LevelBeginMessage.cpp
        LevelBeginMessage.h
        ItemVisitor.cpp
        ItemVisitor.h
        DeclarationVisitor.cpp
        DeclarationVisitor.h
        GetItemVisitor.cpp
        GetItemVisitor.h
        GetDeclarationVisitor.cpp
        GetDeclarationVisitor.h
        SudokuBoard.cpp
        SudokuBoard.h
        GetDigitVisitor.cpp
        GetDigitVisitor.h
        GetNumberDeclaration.cpp
        GetNumberDeclaration.h
        NumberEvaluator.cpp
        NumberEvaluator.h
        XRayRetrieveVisitor.cpp
        XRayRetrieveVisitor.h
        Alert.cpp
        Alert.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
