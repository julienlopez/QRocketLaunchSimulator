#!/bin/bash
cd ..
git clone https://github.com/julienlopez/ETL.git
cd ETL
ls -lh
echo $PWD
sudo ln -s $PWD/etl /usr/include
ls -lh /usr/include