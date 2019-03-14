#!/usr/bin/env python3.6
from numpy import *
from matplotlib.pyplot import *

def GraphGen(Data) :
	x = linspace(0, 360, len(Data.Crypto));
	Hx = linspace(0, 360, len(Data.Crypto));
	CryptoY = array(Data.Crypto);
	RawY = array(Data.Raw);
	StockY = array(Data.Stock);
	ForexY = array(Data.Forex);
	figure();
	subplot(2, 2, 1);
	plot(x, CryptoY);
	plot(Hx, Data.TabHighCrypto);
	plot(Hx, Data.TabLowCrypto);
	title("Crypto");
	subplot(2, 2, 2);
	title("Raw");
	plot(x, RawY);
	plot(Hx, Data.TabHighRaw);
	plot(Hx, Data.TabLowRaw);
	subplot(2, 2, 3);
	title("Stock");
	plot(x, StockY);
	plot(Hx, Data.TabHighStock);
	plot(Hx, Data.TabLowStock);
	subplot(2, 2, 4);
	title("Forex");
	plot(x, ForexY);
	plot(Hx, Data.TabHighForex);
	plot(Hx, Data.TabLowForex);
	show();
