/*
  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, kevin.krammer@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "uitabstopsnode.h"

#include "uinodevisitor.h"
#include "parser.h"

#include <QXmlStreamReader>

UiTabStopsNode::UiTabStopsNode()
{
}

UiNode *UiTabStopsNode::parse(Parser *parser)
{
  UiTabStopsNode *target = new UiTabStopsNode;

  while (!parser->reader()->atEnd()) {
    if (!parser->reader()->readNextStartElement()) {
      if (parser->reader()->isEndElement() && parser->reader()->name().compare("tabstops", Qt::CaseInsensitive) == 0) {
        break;
      } else {
        continue;
      }
    }

    if (parser->reader()->name().compare(QLatin1String("tabstop"), Qt::CaseInsensitive) == 0) {
      target->m_tabStops << parser->reader()->readElementText();
    } else {
      parser->reader()->raiseError(QLatin1String("unsupported tabstops child element ") + parser->reader()->name().toString());
      parser->reader()->skipCurrentElement();
    }
  }

  return target;
}

void UiTabStopsNode::accept(UiNodeVisitor *visitor)
{
  visitor->visit(this);
}

void UiTabStopsNode::setTabStops(const QStringList &tabStops)
{
  m_tabStops = tabStops;
}

QStringList UiTabStopsNode::tabStops() const
{
  return m_tabStops;
}
