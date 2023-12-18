/**
* @file MainFrame.cpp
* @author hankm
*/

#include "pch.h"
#include "MainFrame.h"
#include "SudokuView.h"
#include "ids.h"

/**
 * Initialize the main frame.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sudoku",
           wxDefaultPosition,  wxSize( 1000,800 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto sudokuView = new SudokuView();
    sudokuView->Initialize(this);

    // Add it to the sizer
    sizer->Add(sudokuView,1, wxEXPAND | wxALL );

    mSudokuView = sudokuView;

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    fileMenu->Append(IDM_LEVEL_SOLVE, "Solve", "Solve this level");
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    levelMenu->Append(IDM_LEVEL_LEVEL0, "&Level 0", "Play Level 0");
    levelMenu->Append(IDM_LEVEL_LEVEL1, "&Level 1", "Play Level 1");
    levelMenu->Append(IDM_LEVEL_LEVEL2, "&Level 2", "Play Level 2");
    levelMenu->Append(IDM_LEVEL_LEVEL3, "&Level 3", "Play Level 3");

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(helpMenu, L"&Help");

    SetMenuBar( menuBar );

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mSudokuView->StopTimer();
    Destroy();
}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Welcome to the Sudoku Game!",
                 L"About Sudoku Game",
                 wxOK,
                 this);
}
