/*  SA:MP Functions
 *
 *  ZONES Functions By ~Cueball~
 *  ZONES Functions Aided By Betamaster (locations), Mabako (locations), Simon (finetuning)
 *
 *  (c) Copyright 2005-2008, SA:MP Team
 *
 */

#if defined _zones_included
	#endinput
#endif
#define _zones_included
#pragma library samp
#include <a_samp>

#define MAX_ZONE_NAME 28

//---------------------------------------------------------------------------------------------------

//NATIVES: KEEP THESE COMMENTED! THEY WILL STILL SHOW IN THE RIGHT HAND SIDE OF PAWN!

//native GetPlayer2DZone(playerid, zone[], len);
//native GetPlayer3DZone(playerid, zone[], len);
//native IsPlayerInZone(playerid, zone[]);

//---------------------------------------------------------------------------------------------------

//OUR MAJOR ARRAY: (GLOBAL)

enum MainZone{
Zone_Name[28], Float:Zone_Area[6] };

static const SanAndreasZones[][MainZone] = {

	{"Los Santos",	                {-410.00,1403.30,-3.00,-137.90,1681.20,200.00}},
	{"Los Santos",               {-1372.10,2498.50,0.00,-1277.50,2615.30,200.00}},
	{"Los Santos",                  {-2324.90,-2584.20,-6.10,-1964.20,-2212.10,200.00}},
	{"Los Santos",              {-901.10,2221.80,0.00,-592.00,2571.90,200.00}},
	{"Los Santos",         {-2646.40,-355.40,0.00,-2270.00,-222.50,200.00}},
	{"Los Santos",         {-2831.80,-430.20,-6.10,-2646.40,-222.50,200.00}},
	{"Los Santos",         {-2361.50,-417.10,0.00,-2270.00,-355.40,200.00}},
	{"Los Santos",         {-2667.80,-302.10,-28.80,-2646.40,-262.30,71.10}},
	{"Los Santos",         {-2470.00,-355.40,0.00,-2270.00,-318.40,46.10}},
	{"Los Santos",         {-2550.00,-355.40,0.00,-2470.00,-318.40,39.70}},
	{"Los Santos",               {-1166.90,-2641.10,0.00,-321.70,-1856.00,200.00}},
	{"Los Santos",               {-2741.00,1268.40,-4.50,-2533.00,1490.40,200.00}},
	{"Los Santos",                     {-2741.00,2175.10,0.00,-2353.10,2722.70,200.00}},
	{"Los Santos",              {-2353.10,2275.70,0.00,-2153.10,2475.70,200.00}},
	{"Los Santos",                 {-399.60,-1075.50,-1.40,-319.00,-977.50,198.50}},
	{"Los Santos",                  {964.30,1203.20,-89.00,1197.30,1403.20,110.90}},
	{"Los Santos",                  {964.30,1403.20,-89.00,1197.30,1726.20,110.90}},
	{"Los Santos",           {1375.60,596.30,-89.00,1558.00,823.20,110.90}},
	{"Los Santos",           {1325.60,596.30,-89.00,1375.60,795.00,110.90}},
	{"Los Santos",     {1197.30,1044.60,-89.00,1277.00,1163.30,110.90}},
	{"Los Santos",     {1166.50,795.00,-89.00,1375.60,1044.60,110.90}},
	{"Los Santos",     {1277.00,1044.60,-89.00,1315.30,1087.60,110.90}},
	{"Los Santos",     {1375.60,823.20,-89.00,1457.30,919.40,110.90}},
	{"Los Santos",                   {104.50,-220.10,2.30,349.60,152.20,200.00}},
	{"Los Santos",                   {19.60,-404.10,3.80,349.60,-220.10,200.00}},
	{"Los Santos",             {-319.60,-220.10,0.00,104.50,293.30,200.00}},
	{"Los Santos",           {2087.30,1543.20,-89.00,2437.30,1703.20,110.90}},
	{"Los Santos",           {2137.40,1703.20,-89.00,2437.30,1783.20,110.90}},
	{"Los Santos",              {-2274.10,744.10,-6.10,-1982.30,1358.90,200.00}},
	{"Los Santos",                   {-2274.10,578.30,-7.60,-2078.60,744.10,200.00}},
	{"Los Santos",                   {-2867.80,277.40,-9.10,-2593.40,458.40,200.00}},
	{"Los Santos",                  {2087.30,943.20,-89.00,2623.10,1203.20,110.90}},
	{"Besiktas",                    {1323.90,-1842.20,-89.00,1701.90,-1722.20,110.90}},
	{"Besiktas",                    {1323.90,-1722.20,-89.00,1440.90,-1577.50,110.90}},
	{"Besiktas",                    {1370.80,-1577.50,-89.00,1463.90,-1384.90,110.90}},
	{"Besiktas",                    {1463.90,-1577.50,-89.00,1667.90,-1430.80,110.90}},
	{"Besiktas",                    {1583.50,-1722.20,-89.00,1758.90,-1577.50,110.90}},
	{"Besiktas",                    {1667.90,-1577.50,-89.00,1812.60,-1430.80,110.90}},
	{"Bahcelievler",           {1046.10,-1804.20,-89.00,1323.90,-1722.20,110.90}},
	{"Bahcelievler",           {1073.20,-1842.20,-89.00,1323.90,-1804.20,110.90}},
	{"Los Santos",           {-2007.80,56.30,0.00,-1922.00,224.70,100.00}},
	{"Los Santos",                       {2749.90,1937.20,-89.00,2921.60,2669.70,110.90}},
	{"Los Santos",                   {580.70,-674.80,-9.50,861.00,-404.70,200.00}},
	{"Los Santos",                     {-2270.00,-324.10,-0.00,-1794.90,-222.50,200.00}},
	{"Los Santos",                     {-2173.00,-222.50,-0.00,-1794.90,265.20,200.00}},
	{"Esenler",                    {-1982.30,744.10,-6.10,-1871.70,1274.20,200.00}},
	{"Esenler",                    {-1871.70,1176.40,-4.50,-1620.30,1274.20,200.00}},
	{"Esenler",                    {-1700.00,744.20,-6.10,-1580.00,1176.50,200.00}},
	{"Esenler",                    {-1580.00,744.20,-6.10,-1499.80,1025.90,200.00}},
	{"Esenler",                    {-2078.60,578.30,-7.60,-1499.80,744.20,200.00}},
	{"Esenler",                    {-1993.20,265.20,-9.10,-1794.90,578.30,200.00}},
	{"Gazi Osmanpasa",         {1463.90,-1430.80,-89.00,1724.70,-1290.80,110.90}},
	{"Gazi Osmanpasa",         {1724.70,-1430.80,-89.00,1812.60,-1250.90,110.90}},
	{"Gazi Osmanpasa",         {1463.90,-1290.80,-89.00,1724.70,-1150.80,110.90}},
	{"Gazi Osmanpasa",         {1370.80,-1384.90,-89.00,1463.90,-1170.80,110.90}},
	{"Gazi Osmanpasa",         {1724.70,-1250.90,-89.00,1812.60,-1150.80,110.90}},
	{"Esenler",         {1370.80,-1170.80,-89.00,1463.90,-1130.80,110.90}},
	{"Esenler",         {1378.30,-1130.80,-89.00,1463.90,-1026.30,110.90}},
	{"Esenler",         {1391.00,-1026.30,-89.00,1463.90,-926.90,110.90}},
	{"Esenler",         {1507.50,-1385.20,110.90,1582.50,-1325.30,335.90}},
	{"Olimpiyat Stadi",             {2632.80,-1852.80,-89.00,2959.30,-1668.10,110.90}},
	{"Olimpiyat Stadi",             {2632.80,-1668.10,-89.00,2747.70,-1393.40,110.90}},
	{"Olimpiyat Stadi",             {2747.70,-1668.10,-89.00,2959.30,-1498.60,110.90}},
	{"Olimpiyat Stadi",             {2747.70,-1498.60,-89.00,2959.30,-1120.00,110.90}},
	{"Eyup",             {2421.00,-1628.50,-89.00,2632.80,-1454.30,110.90}},
	{"Eyup",             {2222.50,-1628.50,-89.00,2421.00,-1494.00,110.90}},
	{"Eyup",             {2266.20,-1494.00,-89.00,2381.60,-1372.00,110.90}},
	{"Eyup",             {2381.60,-1494.00,-89.00,2421.00,-1454.30,110.90}},
	{"Eyup",             {2281.40,-1372.00,-89.00,2381.60,-1135.00,110.90}},
	{"Eyup",             {2381.60,-1454.30,-89.00,2462.10,-1135.00,110.90}},
	{"Eyup",             {2462.10,-1454.30,-89.00,2581.70,-1135.00,110.90}},
	{"Los Santos",                {-1794.90,249.90,-9.10,-1242.90,578.30,200.00}},
	{"Los Santos",                {-1794.90,-50.00,-0.00,-1499.80,249.90,200.00}},
	{"Havaalani",          {-1499.80,-50.00,-0.00,-1242.90,249.90,200.00}},
	{"Havaalani",          {-1794.90,-730.10,-3.00,-1213.90,-50.00,200.00}},
	{"Havaalani",          {-1213.90,-730.10,0.00,-1132.80,-50.00,200.00}},
	{"Havaalani",          {-1242.90,-50.00,0.00,-1213.90,578.30,200.00}},
	{"Havaalani",          {-1213.90,-50.00,-4.50,-947.90,578.30,200.00}},
	{"Havaalani",          {-1315.40,-405.30,15.40,-1264.40,-209.50,25.40}},
	{"Havaalani",          {-1354.30,-287.30,15.40,-1315.40,-209.50,25.40}},
	{"Havaalani",          {-1490.30,-209.50,15.40,-1264.40,-148.30,25.40}},
	{"Los Santos",        {-1132.80,-768.00,0.00,-956.40,-578.10,200.00}},
	{"Los Santos",        {-1132.80,-787.30,0.00,-956.40,-768.00,200.00}},
	{"Los Santos",      {-464.50,2217.60,0.00,-208.50,2580.30,200.00}},
	{"Los Santos",      {-208.50,2123.00,-7.60,114.00,2337.10,200.00}},
	{"Los Santos",      {-208.50,2337.10,0.00,8.40,2487.10,200.00}},
	{"Bayrampasa",                   {1812.60,-2179.20,-89.00,1970.60,-1852.80,110.90}},
	{"Bayrampasa",                   {1692.60,-2179.20,-89.00,1812.60,-1842.20,110.90}},
	{"Los Santos",                {-1645.20,2498.50,0.00,-1372.10,2777.80,200.00}},
	{"Los Santos",              {-1620.30,1176.50,-4.50,-1580.00,1274.20,200.00}},
	{"Los Santos",              {-1580.00,1025.90,-6.10,-1499.80,1274.20,200.00}},
	{"Los Santos",              {-1499.80,578.30,-79.60,-1339.80,1274.20,20.30}},
	{"Los Santos",             {-2533.00,1358.90,-4.50,-1996.60,1501.20,200.00}},
	{"Los Santos",             {-1996.60,1358.90,-4.50,-1524.20,1592.50,200.00}},
	{"Los Santos",             {-1982.30,1274.20,-4.50,-1524.20,1358.90,200.00}},
	{"Los Santos",                 {-792.20,-698.50,-5.30,-452.40,-380.00,200.00}},
	{"Los Santos",               {434.30,366.50,0.00,603.00,555.60,200.00}},
	{"Los Santos",                  {508.10,-139.20,0.00,1306.60,119.50,200.00}},
	{"Los Santos",                   {-1871.70,744.10,-6.10,-1701.30,1176.40,300.00}},
	{"Los Santos",             {1916.90,-233.30,-100.00,2131.70,13.80,200.00}},
	{"Los Santos",          {-187.70,-1596.70,-89.00,17.00,-1276.60,110.90}},
	{"Los Santos",                 {-594.10,-1648.50,0.00,-187.70,-1276.60,200.00}},
	{"Los Santos",                 {-376.20,826.30,-3.00,123.70,1220.40,200.00}},
	{"Los Santos",               {-2270.00,-430.20,-0.00,-2178.60,-324.10,200.00}},
	{"Los Santos",               {-2178.60,-599.80,-0.00,-1794.90,-324.10,200.00}},
	{"Los Santos",               {-2178.60,-1115.50,0.00,-1794.90,-599.80,200.00}},
	{"Los Santos",               {-2178.60,-1250.90,0.00,-1794.90,-1115.50,200.00}},
	{"Los Santos",            {2759.20,296.50,0.00,2774.20,594.70,200.00}},
	{"Los Santos",                 {-2741.40,1659.60,-6.10,-2616.40,2175.10,200.00}},
	{"Los Santos",                 {-2741.00,1490.40,-6.10,-2616.40,1659.60,200.00}},
	{"Los Santos",                      {2222.50,-1852.80,-89.00,2632.80,-1722.30,110.90}},
	{"Los Santos",                      {2222.50,-1722.30,-89.00,2632.80,-1628.50,110.90}},
	{"Los Santos",                      {-2411.20,-222.50,-0.00,-2173.00,265.20,200.00}},
	{"Los Santos",                      {-2395.10,-222.50,-5.30,-2354.00,-204.70,200.00}},
	{"Los Santos",               {-1339.80,828.10,-89.00,-1213.90,1057.00,110.90}},
	{"Los Santos",               {-1213.90,950.00,-89.00,-1087.90,1178.90,110.90}},
	{"Los Santos",               {-1499.80,696.40,-179.60,-1339.80,925.30,20.30}},
	{"Gazi Osmanpasa",                   {1812.60,-1449.60,-89.00,1996.90,-1350.70,110.90}},
	{"Gazi Osmanpasa",                   {1812.60,-1100.80,-89.00,1994.30,-973.30,110.90}},
	{"Gazi Osmanpasa",                   {1812.60,-1350.70,-89.00,2056.80,-1100.80,110.90}},
	{"Los Santos",                 {176.50,1305.40,-3.00,338.60,1520.70,200.00}},
	{"Los Santos",          {964.30,1044.60,-89.00,1197.30,1203.20,110.90}},
	{"Los Santos",          {964.30,930.80,-89.00,1166.50,1044.60,110.90}},
	{"Los Santos",               {603.00,264.30,0.00,761.90,366.50,200.00}},
	{"Los Santos",            {2576.90,62.10,0.00,2759.20,385.50,200.00}},
	{"Los Santos",          {1777.30,863.20,-89.00,1817.30,2342.80,110.90}},
	{"Los Santos",                    {-2593.40,-222.50,-0.00,-2411.20,54.70,200.00}},
	{"Los Santos",                {967.30,-450.30,-3.00,1176.70,-217.90,200.00}},
	{"Los Santos",               {337.20,710.80,-115.20,860.50,1031.70,203.70}},
	{"Haydarpasa",                    {1812.60,-1852.80,-89.00,1971.60,-1742.30,110.90}},
	{"Haydarpasa",                    {1812.60,-1742.30,-89.00,1951.60,-1602.30,110.90}},
	{"Haydarpasa",                    {1951.60,-1742.30,-89.00,2124.60,-1602.30,110.90}},
	{"Haydarpasa",                    {1812.60,-1602.30,-89.00,2124.60,-1449.60,110.90}},
	{"Haydarpasa",                    {2124.60,-1742.30,-89.00,2222.50,-1494.00,110.90}},
	{"Haydarpasa",                    {1971.60,-1852.80,-89.00,2222.50,-1742.30,110.90}},
	{"Eyup",                   {1996.90,-1449.60,-89.00,2056.80,-1350.70,110.90}},
	{"Eyup",                   {2124.60,-1494.00,-89.00,2266.20,-1449.60,110.90}},
	{"Eyup",                   {2056.80,-1372.00,-89.00,2281.40,-1210.70,110.90}},
	{"Eyup",                   {2056.80,-1210.70,-89.00,2185.30,-1126.30,110.90}},
	{"Eyup",                   {2185.30,-1210.70,-89.00,2281.40,-1154.50,110.90}},
	{"Eyup",                   {2056.80,-1449.60,-89.00,2266.20,-1372.00,110.90}},
	{"Los Santos",         {2623.10,943.20,-89.00,2749.90,1055.90,110.90}},
	{"Los Santos",         {2685.10,1055.90,-89.00,2749.90,2626.50,110.90}},
	{"Los Santos",         {2536.40,2442.50,-89.00,2685.10,2542.50,110.90}},
	{"Los Santos",         {2625.10,2202.70,-89.00,2685.10,2442.50,110.90}},
	{"Los Santos",        {2498.20,2542.50,-89.00,2685.10,2626.50,110.90}},
	{"Los Santos",        {2237.40,2542.50,-89.00,2498.20,2663.10,110.90}},
	{"Los Santos",        {2121.40,2508.20,-89.00,2237.40,2663.10,110.90}},
	{"Los Santos",        {1938.80,2508.20,-89.00,2121.40,2624.20,110.90}},
	{"Los Santos",        {1534.50,2433.20,-89.00,1848.40,2583.20,110.90}},
	{"Los Santos",        {1848.40,2478.40,-89.00,1938.80,2553.40,110.90}},
	{"Los Santos",        {1704.50,2342.80,-89.00,1848.40,2433.20,110.90}},
	{"Los Santos",        {1377.30,2433.20,-89.00,1534.50,2507.20,110.90}},
	{"Los Santos",        {1457.30,823.20,-89.00,2377.30,863.20,110.90}},
	{"Los Santos",        {2377.30,788.80,-89.00,2537.30,897.90,110.90}},
	{"Los Santos",         {1197.30,1163.30,-89.00,1236.60,2243.20,110.90}},
	{"Los Santos",         {1236.60,2142.80,-89.00,1297.40,2243.20,110.90}},
	{"Los Santos",                {-2533.00,578.30,-7.60,-2274.10,968.30,200.00}},
	{"Los Santos",              {-2533.00,968.30,-6.10,-2274.10,1358.90,200.00}},
	{"Los Santos",     {2498.20,2626.50,-89.00,2749.90,2861.50,110.90}},
	{"Los Santos",              {-1339.80,599.20,-89.00,-1213.90,828.10,110.90}},
	{"Los Santos",              {-1213.90,721.10,-89.00,-1087.90,950.00,110.90}},
	{"Los Santos",              {-1087.90,855.30,-89.00,-961.90,986.20,110.90}},
	{"Los Santos",                      {-2329.30,458.40,-7.60,-1993.20,578.30,200.00}},
	{"Los Santos",                      {-2411.20,265.20,-9.10,-1993.20,373.50,200.00}},
	{"Los Santos",                      {-2253.50,373.50,-9.10,-1993.20,458.40,200.00}},
	{"Los Santos",           {1457.30,863.20,-89.00,1777.40,1143.20,110.90}},
	{"Los Santos",           {1375.60,919.40,-89.00,1457.30,1203.20,110.90}},
	{"Los Santos",           {1277.00,1087.60,-89.00,1375.60,1203.20,110.90}},
	{"Los Santos",           {1315.30,1044.60,-89.00,1375.60,1087.60,110.90}},
	{"Los Santos",           {1236.60,1163.40,-89.00,1277.00,1203.20,110.90}},
	{"Los Santos",               {-926.10,1398.70,-3.00,-719.20,1634.60,200.00}},
	{"Los Santos",                  {-365.10,2123.00,-3.00,-208.50,2217.60,200.00}},
	{"Los Santos",                 {1994.30,-1100.80,-89.00,2056.80,-920.80,110.90}},
	{"Los Santos",                 {2056.80,-1126.30,-89.00,2126.80,-920.80,110.90}},
	{"Los Santos",                 {2185.30,-1154.50,-89.00,2281.40,-934.40,110.90}},
	{"Los Santos",                 {2126.80,-1126.30,-89.00,2185.30,-934.40,110.90}},
	{"Los Santos",                 {2747.70,-1120.00,-89.00,2959.30,-945.00,110.90}},
	{"Las Colinas",                 {2632.70,-1135.00,-89.00,2747.70,-945.00,110.90}},
	{"Las Colinas",                 {2281.40,-1135.00,-89.00,2632.70,-945.00,110.90}},
	{"Las Payasadas",               {-354.30,2580.30,2.00,-133.60,2816.80,200.00}},
	{"Las Venturas Airport",        {1236.60,1203.20,-89.00,1457.30,1883.10,110.90}},
	{"Las Venturas Airport",        {1457.30,1203.20,-89.00,1777.30,1883.10,110.90}},
	{"Las Venturas Airport",        {1457.30,1143.20,-89.00,1777.40,1203.20,110.90}},
	{"Las Venturas Airport",        {1515.80,1586.40,-12.50,1729.90,1714.50,87.50}},
	{"Last Dime Motel",             {1823.00,596.30,-89.00,1997.20,823.20,110.90}},
	{"Leafy Hollow",                {-1166.90,-1856.00,0.00,-815.60,-1602.00,200.00}},
	{"Liberty City",                {-1000.00,400.00,1300.00,-700.00,600.00,1400.00}},
	{"Lil' Probe Inn",              {-90.20,1286.80,-3.00,153.80,1554.10,200.00}},
	{"Linden Side",                 {2749.90,943.20,-89.00,2923.30,1198.90,110.90}},
	{"Linden Station",              {2749.90,1198.90,-89.00,2923.30,1548.90,110.90}},
	{"Linden Station",              {2811.20,1229.50,-39.50,2861.20,1407.50,60.40}},
	{"Dolmabahce",	                {1701.90,-1842.20,-89.00,1812.60,-1722.20,110.90}},
	{"Dolmabahce",  	            {1758.90,-1722.20,-89.00,1812.60,-1577.50,110.90}},
	{"Los Flores",                  {2581.70,-1454.30,-89.00,2632.80,-1393.40,110.90}},
	{"Los Flores",                  {2581.70,-1393.40,-89.00,2747.70,-1135.00,110.90}},
	{"Bakirkoy",    {1249.60,-2394.30,-89.00,1852.00,-2179.20,110.90}},
	{"Bakirkoy",    {1852.00,-2394.30,-89.00,2089.00,-2179.20,110.90}},
	{"Bakirkoy",    {1382.70,-2730.80,-89.00,2201.80,-2394.30,110.90}},
	{"Bakirkoy",    {1974.60,-2394.30,-39.00,2089.00,-2256.50,60.90}},
	{"Bakirkoy",    {1400.90,-2669.20,-39.00,2189.80,-2597.20,60.90}},
	{"Bakirkoy",    {2051.60,-2597.20,-39.00,2152.40,-2394.30,60.90}},
	{"Avcilar",                      {647.70,-1804.20,-89.00,851.40,-1577.50,110.90}},
	{"Avcilar",                      {647.70,-1577.50,-89.00,807.90,-1416.20,110.90}},
	{"Avcilar",                      {807.90,-1577.50,-89.00,926.90,-1416.20,110.90}},
	{"Kucuk Cekmece",                      {787.40,-1416.20,-89.00,1072.60,-1310.20,110.90}},
	{"Kucuk Cekmece",                      {952.60,-1310.20,-89.00,1072.60,-1130.80,110.90}},
	{"Kucuk Cekmece",                      {1072.60,-1416.20,-89.00,1370.80,-1130.80,110.90}},
	{"Kucuk Cekmece",                      {926.90,-1577.50,-89.00,1370.80,-1416.20,110.90}},
	{"Kucuk Cekmece",              {787.40,-1410.90,-34.10,866.00,-1310.20,65.80}},
	{"Martin Bridge",               {-222.10,293.30,0.00,-122.10,476.40,200.00}},
	{"Missionary Hill",             {-2994.40,-811.20,0.00,-2178.60,-430.20,200.00}},
	{"Beykoz",                  {1119.50,119.50,-3.00,1451.40,493.30,200.00}},
	{"Beykoz",                  {1451.40,347.40,-6.10,1582.40,420.80,200.00}},
	{"Beykoz",     {1546.60,208.10,0.00,1745.80,347.40,200.00}},
	{"Beykoz",     {1582.40,347.40,0.00,1664.60,401.70,200.00}},
	{"Catalca",                  {1414.00,-768.00,-89.00,1667.60,-452.40,110.90}},
	{"Catalca",                  {1281.10,-452.40,-89.00,1641.10,-290.90,110.90}},
	{"Catalca",                  {1269.10,-768.00,-89.00,1414.00,-452.40,110.90}},
	{"Catalca",                  {1357.00,-926.90,-89.00,1463.90,-768.00,110.90}},
	{"Catalca",                  {1318.10,-910.10,-89.00,1357.00,-768.00,110.90}},
	{"Catalca",                  {1169.10,-910.10,-89.00,1318.10,-768.00,110.90}},
	{"Catalca",                  {768.60,-954.60,-89.00,952.60,-860.60,110.90}},
	{"Kucuk Cekmece",                  {687.80,-860.60,-89.00,911.80,-768.00,110.90}},
	{"Kucuk Cekmece",                  {737.50,-768.00,-89.00,1142.20,-674.80,110.90}},
	{"Kucuk Cekmece",                  {1096.40,-910.10,-89.00,1169.10,-768.00,110.90}},
	{"Kucuk Cekmece",                  {952.60,-937.10,-89.00,1096.40,-860.60,110.90}},
	{"Kucuk Cekmece",                  {911.80,-860.60,-89.00,1096.40,-768.00,110.90}},
	{"Kucuk Cekmece",                  {861.00,-674.80,-89.00,1156.50,-600.80,110.90}},
	{"Gazi Osman Pasa",     {1463.90,-1150.80,-89.00,1812.60,-768.00,110.90}},
	{"North Rock",                  {2285.30,-768.00,0.00,2770.50,-269.70,200.00}},
	{"Kadikoy Sahil Yolu",         	{2373.70,-2697.00,-89.00,2809.20,-2330.40,110.90}},
	{"Kadikoy Sahil Yolu",          {2201.80,-2418.30,-89.00,2324.00,-2095.00,110.90}},
	{"Kadikoy Sahil Yolu",          {2324.00,-2302.30,-89.00,2703.50,-2145.10,110.90}},
	{"Kadikoy Sahil Yolu",          {2089.00,-2394.30,-89.00,2201.80,-2235.80,110.90}},
	{"Kadikoy Sahil Yolu",          {2201.80,-2730.80,-89.00,2324.00,-2418.30,110.90}},
	{"Kadikoy Sahil Yolu",          {2703.50,-2302.30,-89.00,2959.30,-2126.90,110.90}},
	{"Kadikoy Sahil Yolu",          {2324.00,-2145.10,-89.00,2703.50,-2059.20,110.90}},
	{"Ocean Flats",                 {-2994.40,277.40,-9.10,-2867.80,458.40,200.00}},
	{"Ocean Flats",                 {-2994.40,-222.50,-0.00,-2593.40,277.40,200.00}},
	{"Ocean Flats",                 {-2994.40,-430.20,-0.00,-2831.80,-222.50,200.00}},
	{"Octane Springs",              {338.60,1228.50,0.00,664.30,1655.00,200.00}},
	{"Old Venturas Strip",          {2162.30,2012.10,-89.00,2685.10,2202.70,110.90}},
	{"Palisades",                   {-2994.40,458.40,-6.10,-2741.00,1339.60,200.00}},
	{"Sile",              {2160.20,-149.00,0.00,2576.90,228.30,200.00}},
	{"Paradiso",                    {-2741.00,793.40,-6.10,-2533.00,1268.40,200.00}},
	{"Taksim",             {1440.90,-1722.20,-89.00,1583.50,-1577.50,110.90}},
	{"Pilgrim",                     {2437.30,1383.20,-89.00,2624.40,1783.20,110.90}},
	{"Pilgrim",                     {2624.40,1383.20,-89.00,2685.10,1783.20,110.90}},
	{"Pilson Intersection",         {1098.30,2243.20,-89.00,1377.30,2507.20,110.90}},
	{"Pirates in Men's Pants",      {1817.30,1469.20,-89.00,2027.40,1703.20,110.90}},
	{"Modaa Sahil Yolu",           {2703.50,-2126.90,-89.00,2959.30,-1852.80,110.90}},
	{"Prickle Pine",                {1534.50,2583.20,-89.00,1848.40,2863.20,110.90}},
	{"Prickle Pine",                {1117.40,2507.20,-89.00,1534.50,2723.20,110.90}},
	{"Prickle Pine",                {1848.40,2553.40,-89.00,1938.80,2863.20,110.90}},
	{"Prickle Pine",                {1938.80,2624.20,-89.00,2121.40,2861.50,110.90}},
	{"Queens",                      {-2533.00,458.40,0.00,-2329.30,578.30,200.00}},
	{"Queens",                      {-2593.40,54.70,0.00,-2411.20,458.40,200.00}},
	{"Queens",                      {-2411.20,373.50,0.00,-2253.50,458.40,200.00}},
	{"Randolph Industrial Estate",  {1558.00,596.30,-89.00,1823.00,823.20,110.90}},
	{"Redsands East",               {1817.30,2011.80,-89.00,2106.70,2202.70,110.90}},
	{"Redsands East",               {1817.30,2202.70,-89.00,2011.90,2342.80,110.90}},
	{"Redsands East",               {1848.40,2342.80,-89.00,2011.90,2478.40,110.90}},
	{"Redsands West",               {1236.60,1883.10,-89.00,1777.30,2142.80,110.90}},
	{"Redsands West",               {1297.40,2142.80,-89.00,1777.30,2243.20,110.90}},
	{"Redsands West",               {1377.30,2243.20,-89.00,1704.50,2433.20,110.90}},
	{"Redsands West",               {1704.50,2243.20,-89.00,1777.30,2342.80,110.90}},
	{"Regular Tom",                 {-405.70,1712.80,-3.00,-276.70,1892.70,200.00}},
	{"Kucuk Cekmece",                     {647.50,-1118.20,-89.00,787.40,-954.60,110.90}},
	{"Kucuk Cekmece",                     {647.50,-954.60,-89.00,768.60,-860.60,110.90}},
	{"Kucuk Cekmece",                     {225.10,-1369.60,-89.00,334.50,-1292.00,110.90}},
	{"Kucuk Cekmece",                     {225.10,-1292.00,-89.00,466.20,-1235.00,110.90}},
	{"Kucuk Cekmece",                     {72.60,-1404.90,-89.00,225.10,-1235.00,110.90}},
	{"Kucuk Cekmece",                     {72.60,-1235.00,-89.00,321.30,-1008.10,110.90}},
	{"Kucuk Cekmece",                     {321.30,-1235.00,-89.00,647.50,-1044.00,110.90}},
	{"Kucuk Cekmece",                     {321.30,-1044.00,-89.00,647.50,-860.60,110.90}},
	{"Kucuk Cekmece",                     {321.30,-860.60,-89.00,687.80,-768.00,110.90}},
	{"Kucuk Cekmece",                     {321.30,-768.00,-89.00,700.70,-674.80,110.90}},
	{"Robada Intersection",         {-1119.00,1178.90,-89.00,-862.00,1351.40,110.90}},
	{"Roca Escalante",              {2237.40,2202.70,-89.00,2536.40,2542.50,110.90}},
	{"Roca Escalante",              {2536.40,2202.70,-89.00,2625.10,2442.50,110.90}},
	{"Rockshore East",              {2537.30,676.50,-89.00,2902.30,943.20,110.90}},
	{"Rockshore West",              {1997.20,596.30,-89.00,2377.30,823.20,110.90}},
	{"Rockshore West",              {2377.30,596.30,-89.00,2537.30,788.80,110.90}},
	{"Buyuk Cekmece",                       {72.60,-1684.60,-89.00,225.10,-1544.10,110.90}},
	{"Buyuk Cekmece",                       {72.60,-1544.10,-89.00,225.10,-1404.90,110.90}},
	{"Buyuk Cekmece",                       {225.10,-1684.60,-89.00,312.80,-1501.90,110.90}},
	{"Buyuk Cekmece",                       {225.10,-1501.90,-89.00,334.50,-1369.60,110.90}},
	{"Buyuk Cekmece",                       {334.50,-1501.90,-89.00,422.60,-1406.00,110.90}},
	{"Buyuk Cekmece",                       {312.80,-1684.60,-89.00,422.60,-1501.90,110.90}},
	{"Buyuk Cekmece",                       {422.60,-1684.60,-89.00,558.00,-1570.20,110.90}},
	{"Buyuk Cekmece",                       {558.00,-1684.60,-89.00,647.50,-1384.90,110.90}},
	{"Buyuk Cekmece",                       {466.20,-1570.20,-89.00,558.00,-1385.00,110.90}},
	{"Buyuk Cekmece",                       {422.60,-1570.20,-89.00,466.20,-1406.00,110.90}},
	{"Buyuk Cekmece",                       {466.20,-1385.00,-89.00,647.50,-1235.00,110.90}},
	{"Buyuk Cekmece",                       {334.50,-1406.00,-89.00,466.20,-1292.00,110.90}},
	{"Royal Casino",                {2087.30,1383.20,-89.00,2437.30,1543.20,110.90}},
	{"San Andreas Sound",           {2450.30,385.50,-100.00,2759.20,562.30,200.00}},
	{"Metro Flora",                 {-2741.00,458.40,-7.60,-2533.00,793.40,200.00}},
	{"Buyuk Cekmece Sahili",           {342.60,-2173.20,-89.00,647.70,-1684.60,110.90}},
	{"Buyuk Cekmece Sahili",           {72.60,-2173.20,-89.00,342.60,-1684.60,110.90}},
	{"Shady Cabin",                 {-1632.80,-2263.40,-3.00,-1601.30,-2231.70,200.00}},
	{"Shady Creeks",                {-1820.60,-2643.60,-8.00,-1226.70,-1771.60,200.00}},
	{"Shady Creeks",                {-2030.10,-2174.80,-6.10,-1820.60,-1771.60,200.00}},
	{"Sobell Rail Yards",           {2749.90,1548.90,-89.00,2923.30,1937.20,110.90}},
	{"Spinybed",                    {2121.40,2663.10,-89.00,2498.20,2861.50,110.90}},
	{"Starfish Casino",             {2437.30,1783.20,-89.00,2685.10,2012.10,110.90}},
	{"Starfish Casino",             {2437.30,1858.10,-39.00,2495.00,1970.80,60.90}},
	{"Starfish Casino",             {2162.30,1883.20,-89.00,2437.30,2012.10,110.90}},
	{"Kucuk Cekmece",                      {1252.30,-1130.80,-89.00,1378.30,-1026.30,110.90}},
	{"Kucuk Cekmece",                      {1252.30,-1026.30,-89.00,1391.00,-926.90,110.90}},
	{"Kucuk Cekmece",                      {1252.30,-926.90,-89.00,1357.00,-910.10,110.90}},
	{"Kucuk Cekmece",                      {952.60,-1130.80,-89.00,1096.40,-937.10,110.90}},
	{"Kucuk Cekmece",                      {1096.40,-1130.80,-89.00,1252.30,-1026.30,110.90}},
	{"Kucuk Cekmece",                      {1096.40,-1026.30,-89.00,1252.30,-910.10,110.90}},
	{"The Camel's Toe",             {2087.30,1203.20,-89.00,2640.40,1383.20,110.90}},
	{"The Clown's Pocket",          {2162.30,1783.20,-89.00,2437.30,1883.20,110.90}},
	{"Izmir",            {2011.90,2202.70,-89.00,2237.40,2508.20,110.90}},
	{"The Farm",                    {-1209.60,-1317.10,114.90,-908.10,-787.30,251.90}},
	{"The Four Dragons Casino",     {1817.30,863.20,-89.00,2027.30,1083.20,110.90}},
	{"The High Roller",             {1817.30,1283.20,-89.00,2027.30,1469.20,110.90}},
	{"The Mako Span",               {1664.60,401.70,0.00,1785.10,567.20,200.00}},
	{"The Panopticon",              {-947.90,-304.30,-1.10,-319.60,327.00,200.00}},
	{"The Pink Swan",               {1817.30,1083.20,-89.00,2027.30,1283.20,110.90}},
	{"The Sherman Dam",             {-968.70,1929.40,-3.00,-481.10,2155.20,200.00}},
	{"The Strip",                   {2027.40,863.20,-89.00,2087.30,1703.20,110.90}},
	{"The Strip",                   {2106.70,1863.20,-89.00,2162.30,2202.70,110.90}},
	{"The Strip",                   {2027.40,1783.20,-89.00,2162.30,1863.20,110.90}},
	{"The Strip",                   {2027.40,1703.20,-89.00,2137.40,1783.20,110.90}},
	{"The Visage",                  {1817.30,1863.20,-89.00,2106.70,2011.80,110.90}},
	{"The Visage",                  {1817.30,1703.20,-89.00,2027.40,1863.20,110.90}},
	{"Unity Station",               {1692.60,-1971.80,-20.40,1812.60,-1932.80,79.50}},
	{"Valle Ocultado",              {-936.60,2611.40,2.00,-715.90,2847.90,200.00}},
	{"Ortakoy",             		{930.20,-2488.40,-89.00,1249.60,-2006.70,110.90}},
	{"Ortakoy",             	 	{1073.20,-2006.70,-89.00,1249.60,-1842.20,110.90}},
	{"Ortakoy",             		{1249.60,-2179.20,-89.00,1692.60,-1842.20,110.90}},
	{"Verdant Meadows",             {37.00,2337.10,-3.00,435.90,2677.90,200.00}},
	{"Avcilar Sahili",                {647.70,-2173.20,-89.00,930.20,-1804.20,110.90}},
	{"Avcilar Sahili",                {930.20,-2006.70,-89.00,1073.20,-1804.20,110.90}},
	{"Avcilar Sahili",                {851.40,-1804.20,-89.00,1046.10,-1577.50,110.90}},
	{"Avcilar Sahili",                {1161.50,-1722.20,-89.00,1323.90,-1577.50,110.90}},
	{"Avcilar Sahili",                {1046.10,-1722.20,-89.00,1161.50,-1577.50,110.90}},
	{"Kucuk Cekmece",                    {787.40,-1310.20,-89.00,952.60,-1130.80,110.90}},
	{"Kucuk Cekmece",                    {787.40,-1130.80,-89.00,952.60,-954.60,110.90}},
	{"Kucuk Cekmece",                    {647.50,-1227.20,-89.00,787.40,-1118.20,110.90}},
	{"Kucuk Cekmece",                    {647.70,-1416.20,-89.00,787.40,-1227.20,110.90}},
	{"Whitewood Estates",           {883.30,1726.20,-89.00,1098.30,2507.20,110.90}},
	{"Whitewood Estates",           {1098.30,1726.20,-89.00,1197.30,2243.20,110.90}},
	{"Umraniye",                 {1970.60,-2179.20,-89.00,2089.00,-1852.80,110.90}},
	{"Umraniye",                 {2089.00,-2235.80,-89.00,2201.80,-1989.90,110.90}},
	{"Umraniye",                 {2089.00,-1989.90,-89.00,2324.00,-1852.80,110.90}},
	{"Umraniye",                 {2201.80,-2095.00,-89.00,2324.00,-1989.90,110.90}},
	{"Umraniye",                 {2541.70,-1941.40,-89.00,2703.50,-1852.80,110.90}},
	{"Umraniye",                 {2324.00,-2059.20,-89.00,2541.70,-1852.80,110.90}},
	{"Umraniye",                 {2541.70,-2059.20,-89.00,2703.50,-1941.40,110.90}},
	{"Yellow Bell Station",         {1377.40,2600.40,-21.90,1492.40,2687.30,78.00}},
	// Main Zones
	{"Los Santos",                  {44.60,-2892.90,-242.90,2997.00,-768.00,900.00}},
	{"Bursa",                {869.40,596.30,-242.90,2997.00,2993.80,900.00}},
	{"Los Santos",                 {-480.50,596.30,-242.90,869.40,2993.80,900.00}},
	{"Los Santos",               {-2997.40,1659.60,-242.90,-480.50,2993.80,900.00}},
	{"Los Santos",               {-1213.90,596.30,-242.90,-480.50,1659.60,900.00}},
	{"Tekirdağ",                  {-2997.40,-1115.50,-242.90,-1213.90,1659.60,900.00}},
	{"Los Santos",                  {-1213.90,-768.00,-242.90,2997.00,596.30,900.00}},
	{"Marmara Denizi",                {-1213.90,-2892.90,-242.90,44.60,-768.00,900.00}},
	{"Los Santos",                   {-2997.40,-2892.90,-242.90,-1213.90,-1115.50,900.00}}
};


//---------------------------------------------------------------------------------------------------

/* GetPlayer2DZone(playerid, zone[], len)
 * @Info:   Used to retrieve the players zone/area name. DOES NOT COMPARE HEIGHTS!
 *
 * @params: playerid      - The id of the player whose zone you will retrieve.
 * @params: zone[]        - The string with which the zone name will be formatted into.
 * @params: len		  - The maximum length you wish to format the zone name into. RECOMMENDED 28!
 */

stock GetPlayer2DZone(playerid, zone[], len)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
 	for(new i = 0; i != sizeof(SanAndreasZones); i++ ){
	if(x >= SanAndreasZones[i][Zone_Area][0] && x <= SanAndreasZones[i][Zone_Area][3] && y >= SanAndreasZones[i][Zone_Area][1] && y <= SanAndreasZones[i][Zone_Area][4]){
	return format(zone, len, SanAndreasZones[i][Zone_Name], 0);}
	}
	return 0;
}

//---------------------------------------------------------------------------------------------------

/* GetPlayer3DZone(playerid, zone[], len)
 * @Info:   Used to retrieve the players zone/area name and comparing with heights.
 *
 * @params: playerid      - The id of the player whose zone you will retrieve.
 * @params: zone[]        - The string with which the zone name will be formatted into.
 * @params: len		  - The maximum length you wish to format the zone name into. RECOMMENDED 28!
 */

stock GetPlayer3DZone(playerid, zone[], len)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
 	for(new i = 0; i != sizeof(SanAndreasZones); i++ ){
	if(x >= SanAndreasZones[i][Zone_Area][0] && x <= SanAndreasZones[i][Zone_Area][3] && y >= SanAndreasZones[i][Zone_Area][1] && y <= SanAndreasZones[i][Zone_Area][4] && z >= SanAndreasZones[i][Zone_Area][2] && z <= SanAndreasZones[i][Zone_Area][5]){return format(zone, len, SanAndreasZones[i][Zone_Name], 0);
	}
	}
	return 0;
}

//---------------------------------------------------------------------------------------------------

/* IsPlayerInZone(playerid, zone[])
 * @Info:   Used to check if the player is inside the zone[] parameter.
 *
 * @params: playerid      - The id of the player whose zone you will check.
 * @params: zone[]        - The string with which we will compare the players zone name to.
 */

stock PlayerZone(playerid, zone[])
{
	new ReadTmpZone[MAX_ZONE_NAME];
    GetPlayer3DZone(playerid, ReadTmpZone, sizeof(ReadTmpZone)); for(new i = 0; i != sizeof(SanAndreasZones); i++){
	if(strfind(ReadTmpZone, zone, true) != -1)
	return 1;
	}
	return 0;
}
