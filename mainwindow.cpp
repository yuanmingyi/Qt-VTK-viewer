#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include <vtkNew.h>
#include <vtkDataSetReader.h>
#include <vtkOBJReader.h>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::showAboutDialog()
{
  QMessageBox::information(this, "About", "By Martijn Koopman.\nSource code available under Apache License 2.0.");
}

void MainWindow::showOpenFileDialog()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", "OBJ Files (*.obj)");
  openFile(fileName);
}

void MainWindow::openFile(const QString &fileName)
{
  ui->sceneWidget->removeDataSet();

  // Create reader
  vtkNew<vtkOBJReader> reader;
  reader->SetFileName(fileName.toStdString().c_str());

  // Read the file
  reader->Update();

  // Add data set to 3D view
  vtkSmartPointer<vtkDataSet> dataSet = reader->GetOutput();
  if (dataSet != nullptr)
  {
    ui->sceneWidget->addDataSet(reader->GetOutput());
  }
}
