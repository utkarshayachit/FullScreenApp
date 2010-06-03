/*=========================================================================

   Program: ParaView
   Module:    CustomMainWindow.cxx

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2. 
   
   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

========================================================================*/
#include "CustomMainWindow.h"

#include "pqParaViewBehaviors.h"
#include "pqParaViewMenuBuilders.h"
#include "pqRenderView.h"
#include "pqApplicationCore.h"
#include "pqObjectBuilder.h"
#include "pqActiveObjects.h"
#include "vtkObject.h"

#include <QTimer>

//-----------------------------------------------------------------------------
CustomMainWindow::CustomMainWindow(QWidget* parentObject,
  Qt::WindowFlags wflags) : Superclass(parentObject, wflags)
{
  new pqParaViewBehaviors(this, this);

  pqRenderView* view = qobject_cast<pqRenderView*>(
    pqApplicationCore::instance()->getObjectBuilder()->createView(
      pqRenderView::renderViewType(),
      pqActiveObjects::instance().activeServer()));
  this->setCentralWidget(view->getWidget());
  this->showFullScreen();

  QTimer* timer = new QTimer(this);
  timer->setInterval(0);
  timer->setSingleShot(false);
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(doWorkOnIdle()));
  timer->start();
}

//-----------------------------------------------------------------------------
void CustomMainWindow::doWorkOnIdle()
{
  pqView* view = pqActiveObjects::instance().activeView();
  (void)view;
  
  // Here you can add code to peek for messages from the device and update the
  // camera on the view.
}

//-----------------------------------------------------------------------------
CustomMainWindow::~CustomMainWindow()
{
}
