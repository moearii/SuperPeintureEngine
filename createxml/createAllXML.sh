#!/bin/bash

echo Creation des fichiers xml :

./createxml Kac.cpp Sac.cpp ac.xml
echo ac.xml

./createxml Kbs.cpp Sbs.cpp bs.xml
echo bs.xml

./createxml Kcb.cpp Scb.cpp cb.xml
echo cb.xml

./createxml Kcr.cpp Scr.cpp cr.xml
echo cr.xml

./createxml Kcy.cpp Scy.cpp cy.xml
echo cy.xml

./createxml Kpb.cpp Spb.cpp pb.xml
echo pb.xml

./createxml Ksg.cpp Ssg.cpp sg.xml
echo sg.xml

./createxml Ktw.cpp Stw.cpp tw.xml
echo tw.xml

./createxml Kub.cpp Sub.cpp ub.xml
echo ub.xml

./createxml Kvi.cpp Svi.cpp vi.xml
echo vi.xml

./createxml Kyo.cpp Syo.cpp yo.xml
echo yo.xml

./createxml ciestandardD65.cpp D65.xml
echo D65.xml

./createxml ciestandardA.cpp A.xml
echo A.xml

exit 0