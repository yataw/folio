//{=========================================================================== 
//! @file       Examples/Example01.cpp
//!
//! @brief      ���������� ������ ������������� TXLib.
//!
//!             ���������� ������ ��������� (The Dumb Artist Library, TX Library, TXLib).
//! 
//!             $Version: 0172a, Revision: 133 $
//!             $Date: 2011-04-10 19:06:11 +0400 $
//!             $Copyright: (C) Ded (Ilya Dedinsky, http://ded32.net.ru) $
//              $Author: Ded (Ilya Dedinsky, http://ded32.net.ru) $
//}===========================================================================

#include "TXLib.h"                         // ����������� ���������� ���������

int main()                                 // ��������� ������� �������
    {                                      // ������ �������
    txCreateWindow (800, 600);             // �������� ���� 800 �� 600 ��������

    txLine   (320, 290, 320, 220);         // ���������� ����� �� ����� x=320 � �=290 � ����� � x=320 � y=220
    txLine   (320, 290, 280, 350);         // ���������� ������ �����,    
    txLine   (320, 290, 360, 350);         //     � ���������� ����
    txLine   (320, 230, 270, 275);         //     �� ������ 
    txLine   (320, 230, 400, 220);         //     ���������� �������
    txCircle (320, 190, 30);               // �������� ���������� � ������� x=320 y=190 � �������� 30
                                           
    txSelectFont ("Times", 60);            // ���������� ����� "Times" ������� 60
    txTextOut (240, 400, "Hello, world!"); // ���������� ����� "Hello, world!" � ����� x=240 y=400
    return 0;                              // ������� ��������� ���� ����������
    }                                      // ����� �������
