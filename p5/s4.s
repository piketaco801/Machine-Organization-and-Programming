
s4:     file format elf32-i386


Disassembly of section .init:

00001000 <_init>:
    1000:	f3 0f 1e fb          	endbr32 
    1004:	53                   	push   %ebx
    1005:	83 ec 08             	sub    $0x8,%esp
    1008:	e8 33 01 00 00       	call   1140 <__x86.get_pc_thunk.bx>
    100d:	81 c3 9f 2f 00 00    	add    $0x2f9f,%ebx
    1013:	8b 83 44 00 00 00    	mov    0x44(%ebx),%eax
    1019:	85 c0                	test   %eax,%eax
    101b:	74 02                	je     101f <_init+0x1f>
    101d:	ff d0                	call   *%eax
    101f:	83 c4 08             	add    $0x8,%esp
    1022:	5b                   	pop    %ebx
    1023:	c3                   	ret    

Disassembly of section .plt:

00001030 <__libc_start_main@plt-0x10>:
    1030:	ff b3 04 00 00 00    	push   0x4(%ebx)
    1036:	ff a3 08 00 00 00    	jmp    *0x8(%ebx)
    103c:	00 00                	add    %al,(%eax)
	...

00001040 <__libc_start_main@plt>:
    1040:	ff a3 0c 00 00 00    	jmp    *0xc(%ebx)
    1046:	68 00 00 00 00       	push   $0x0
    104b:	e9 e0 ff ff ff       	jmp    1030 <_init+0x30>

00001050 <free@plt>:
    1050:	ff a3 10 00 00 00    	jmp    *0x10(%ebx)
    1056:	68 08 00 00 00       	push   $0x8
    105b:	e9 d0 ff ff ff       	jmp    1030 <_init+0x30>

00001060 <fgets@plt>:
    1060:	ff a3 14 00 00 00    	jmp    *0x14(%ebx)
    1066:	68 10 00 00 00       	push   $0x10
    106b:	e9 c0 ff ff ff       	jmp    1030 <_init+0x30>

00001070 <sleep@plt>:
    1070:	ff a3 18 00 00 00    	jmp    *0x18(%ebx)
    1076:	68 18 00 00 00       	push   $0x18
    107b:	e9 b0 ff ff ff       	jmp    1030 <_init+0x30>

00001080 <__stack_chk_fail@plt>:
    1080:	ff a3 1c 00 00 00    	jmp    *0x1c(%ebx)
    1086:	68 20 00 00 00       	push   $0x20
    108b:	e9 a0 ff ff ff       	jmp    1030 <_init+0x30>

00001090 <malloc@plt>:
    1090:	ff a3 20 00 00 00    	jmp    *0x20(%ebx)
    1096:	68 28 00 00 00       	push   $0x28
    109b:	e9 90 ff ff ff       	jmp    1030 <_init+0x30>

000010a0 <puts@plt>:
    10a0:	ff a3 24 00 00 00    	jmp    *0x24(%ebx)
    10a6:	68 30 00 00 00       	push   $0x30
    10ab:	e9 80 ff ff ff       	jmp    1030 <_init+0x30>

000010b0 <exit@plt>:
    10b0:	ff a3 28 00 00 00    	jmp    *0x28(%ebx)
    10b6:	68 38 00 00 00       	push   $0x38
    10bb:	e9 70 ff ff ff       	jmp    1030 <_init+0x30>

000010c0 <fopen@plt>:
    10c0:	ff a3 2c 00 00 00    	jmp    *0x2c(%ebx)
    10c6:	68 40 00 00 00       	push   $0x40
    10cb:	e9 60 ff ff ff       	jmp    1030 <_init+0x30>

000010d0 <__printf_chk@plt>:
    10d0:	ff a3 30 00 00 00    	jmp    *0x30(%ebx)
    10d6:	68 48 00 00 00       	push   $0x48
    10db:	e9 50 ff ff ff       	jmp    1030 <_init+0x30>

000010e0 <strtol@plt>:
    10e0:	ff a3 34 00 00 00    	jmp    *0x34(%ebx)
    10e6:	68 50 00 00 00       	push   $0x50
    10eb:	e9 40 ff ff ff       	jmp    1030 <_init+0x30>

000010f0 <__assert_fail@plt>:
    10f0:	ff a3 38 00 00 00    	jmp    *0x38(%ebx)
    10f6:	68 58 00 00 00       	push   $0x58
    10fb:	e9 30 ff ff ff       	jmp    1030 <_init+0x30>

Disassembly of section .plt.got:

00001100 <__cxa_finalize@plt>:
    1100:	ff a3 40 00 00 00    	jmp    *0x40(%ebx)
    1106:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

00001110 <_start>:
    1110:	f3 0f 1e fb          	endbr32 
    1114:	31 ed                	xor    %ebp,%ebp
    1116:	5e                   	pop    %esi
    1117:	89 e1                	mov    %esp,%ecx
    1119:	83 e4 f0             	and    $0xfffffff0,%esp
    111c:	50                   	push   %eax
    111d:	54                   	push   %esp
    111e:	52                   	push   %edx
    111f:	e8 18 00 00 00       	call   113c <_start+0x2c>
    1124:	81 c3 88 2e 00 00    	add    $0x2e88,%ebx
    112a:	6a 00                	push   $0x0
    112c:	6a 00                	push   $0x0
    112e:	51                   	push   %ecx
    112f:	56                   	push   %esi
    1130:	ff b3 4c 00 00 00    	push   0x4c(%ebx)
    1136:	e8 05 ff ff ff       	call   1040 <__libc_start_main@plt>
    113b:	f4                   	hlt    
    113c:	8b 1c 24             	mov    (%esp),%ebx
    113f:	c3                   	ret    

00001140 <__x86.get_pc_thunk.bx>:
    1140:	8b 1c 24             	mov    (%esp),%ebx
    1143:	c3                   	ret    
    1144:	66 90                	xchg   %ax,%ax
    1146:	66 90                	xchg   %ax,%ax
    1148:	66 90                	xchg   %ax,%ax
    114a:	66 90                	xchg   %ax,%ax
    114c:	66 90                	xchg   %ax,%ax
    114e:	66 90                	xchg   %ax,%ax

00001150 <deregister_tm_clones>:
    1150:	e8 e4 00 00 00       	call   1239 <__x86.get_pc_thunk.dx>
    1155:	81 c2 57 2e 00 00    	add    $0x2e57,%edx
    115b:	8d 8a 70 00 00 00    	lea    0x70(%edx),%ecx
    1161:	8d 82 70 00 00 00    	lea    0x70(%edx),%eax
    1167:	39 c8                	cmp    %ecx,%eax
    1169:	74 1d                	je     1188 <deregister_tm_clones+0x38>
    116b:	8b 82 3c 00 00 00    	mov    0x3c(%edx),%eax
    1171:	85 c0                	test   %eax,%eax
    1173:	74 13                	je     1188 <deregister_tm_clones+0x38>
    1175:	55                   	push   %ebp
    1176:	89 e5                	mov    %esp,%ebp
    1178:	83 ec 14             	sub    $0x14,%esp
    117b:	51                   	push   %ecx
    117c:	ff d0                	call   *%eax
    117e:	83 c4 10             	add    $0x10,%esp
    1181:	c9                   	leave  
    1182:	c3                   	ret    
    1183:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    1187:	90                   	nop
    1188:	c3                   	ret    
    1189:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00001190 <register_tm_clones>:
    1190:	e8 a4 00 00 00       	call   1239 <__x86.get_pc_thunk.dx>
    1195:	81 c2 17 2e 00 00    	add    $0x2e17,%edx
    119b:	55                   	push   %ebp
    119c:	89 e5                	mov    %esp,%ebp
    119e:	53                   	push   %ebx
    119f:	8d 8a 70 00 00 00    	lea    0x70(%edx),%ecx
    11a5:	8d 82 70 00 00 00    	lea    0x70(%edx),%eax
    11ab:	83 ec 04             	sub    $0x4,%esp
    11ae:	29 c8                	sub    %ecx,%eax
    11b0:	89 c3                	mov    %eax,%ebx
    11b2:	c1 e8 1f             	shr    $0x1f,%eax
    11b5:	c1 fb 02             	sar    $0x2,%ebx
    11b8:	01 d8                	add    %ebx,%eax
    11ba:	d1 f8                	sar    %eax
    11bc:	74 14                	je     11d2 <register_tm_clones+0x42>
    11be:	8b 92 50 00 00 00    	mov    0x50(%edx),%edx
    11c4:	85 d2                	test   %edx,%edx
    11c6:	74 0a                	je     11d2 <register_tm_clones+0x42>
    11c8:	83 ec 08             	sub    $0x8,%esp
    11cb:	50                   	push   %eax
    11cc:	51                   	push   %ecx
    11cd:	ff d2                	call   *%edx
    11cf:	83 c4 10             	add    $0x10,%esp
    11d2:	8b 5d fc             	mov    -0x4(%ebp),%ebx
    11d5:	c9                   	leave  
    11d6:	c3                   	ret    
    11d7:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    11de:	66 90                	xchg   %ax,%ax

000011e0 <__do_global_dtors_aux>:
    11e0:	f3 0f 1e fb          	endbr32 
    11e4:	55                   	push   %ebp
    11e5:	89 e5                	mov    %esp,%ebp
    11e7:	53                   	push   %ebx
    11e8:	e8 53 ff ff ff       	call   1140 <__x86.get_pc_thunk.bx>
    11ed:	81 c3 bf 2d 00 00    	add    $0x2dbf,%ebx
    11f3:	83 ec 04             	sub    $0x4,%esp
    11f6:	80 bb 70 00 00 00 00 	cmpb   $0x0,0x70(%ebx)
    11fd:	75 27                	jne    1226 <__do_global_dtors_aux+0x46>
    11ff:	8b 83 40 00 00 00    	mov    0x40(%ebx),%eax
    1205:	85 c0                	test   %eax,%eax
    1207:	74 11                	je     121a <__do_global_dtors_aux+0x3a>
    1209:	83 ec 0c             	sub    $0xc,%esp
    120c:	ff b3 58 00 00 00    	push   0x58(%ebx)
    1212:	e8 e9 fe ff ff       	call   1100 <__cxa_finalize@plt>
    1217:	83 c4 10             	add    $0x10,%esp
    121a:	e8 31 ff ff ff       	call   1150 <deregister_tm_clones>
    121f:	c6 83 70 00 00 00 01 	movb   $0x1,0x70(%ebx)
    1226:	8b 5d fc             	mov    -0x4(%ebp),%ebx
    1229:	c9                   	leave  
    122a:	c3                   	ret    
    122b:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    122f:	90                   	nop

00001230 <frame_dummy>:
    1230:	f3 0f 1e fb          	endbr32 
    1234:	e9 57 ff ff ff       	jmp    1190 <register_tm_clones>

00001239 <__x86.get_pc_thunk.dx>:
    1239:	8b 14 24             	mov    (%esp),%edx
    123c:	c3                   	ret    

0000123d <fail>:
    123d:	56                   	push   %esi
    123e:	53                   	push   %ebx
    123f:	83 ec 10             	sub    $0x10,%esp
    1242:	e8 f9 fe ff ff       	call   1140 <__x86.get_pc_thunk.bx>
    1247:	81 c3 65 2d 00 00    	add    $0x2d65,%ebx
    124d:	6a 01                	push   $0x1
    124f:	e8 1c fe ff ff       	call   1070 <sleep@plt>
    1254:	8d b3 5c e0 ff ff    	lea    -0x1fa4(%ebx),%esi
    125a:	89 34 24             	mov    %esi,(%esp)
    125d:	e8 3e fe ff ff       	call   10a0 <puts@plt>
    1262:	8d 83 84 e0 ff ff    	lea    -0x1f7c(%ebx),%eax
    1268:	89 04 24             	mov    %eax,(%esp)
    126b:	e8 30 fe ff ff       	call   10a0 <puts@plt>
    1270:	89 34 24             	mov    %esi,(%esp)
    1273:	e8 28 fe ff ff       	call   10a0 <puts@plt>
    1278:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
    127f:	e8 2c fe ff ff       	call   10b0 <exit@plt>

00001284 <success>:
    1284:	56                   	push   %esi
    1285:	53                   	push   %ebx
    1286:	83 ec 10             	sub    $0x10,%esp
    1289:	e8 b2 fe ff ff       	call   1140 <__x86.get_pc_thunk.bx>
    128e:	81 c3 1e 2d 00 00    	add    $0x2d1e,%ebx
    1294:	6a 01                	push   $0x1
    1296:	e8 d5 fd ff ff       	call   1070 <sleep@plt>
    129b:	8d b3 ac e0 ff ff    	lea    -0x1f54(%ebx),%esi
    12a1:	89 34 24             	mov    %esi,(%esp)
    12a4:	e8 f7 fd ff ff       	call   10a0 <puts@plt>
    12a9:	8d 83 d0 e0 ff ff    	lea    -0x1f30(%ebx),%eax
    12af:	89 04 24             	mov    %eax,(%esp)
    12b2:	e8 e9 fd ff ff       	call   10a0 <puts@plt>
    12b7:	89 34 24             	mov    %esi,(%esp)
    12ba:	e8 e1 fd ff ff       	call   10a0 <puts@plt>
    12bf:	83 c4 14             	add    $0x14,%esp
    12c2:	5b                   	pop    %ebx
    12c3:	5e                   	pop    %esi
    12c4:	c3                   	ret    

000012c5 <insert1>:
    12c5:	53                   	push   %ebx
    12c6:	83 ec 14             	sub    $0x14,%esp
    12c9:	e8 72 fe ff ff       	call   1140 <__x86.get_pc_thunk.bx>
    12ce:	81 c3 de 2c 00 00    	add    $0x2cde,%ebx
    12d4:	6a 08                	push   $0x8
    12d6:	e8 b5 fd ff ff       	call   1090 <malloc@plt>
    12db:	83 c4 10             	add    $0x10,%esp
    12de:	85 c0                	test   %eax,%eax
    12e0:	74 1a                	je     12fc <insert1+0x37>
    12e2:	8b 54 24 10          	mov    0x10(%esp),%edx
    12e6:	89 10                	mov    %edx,(%eax)
    12e8:	8b 93 74 00 00 00    	mov    0x74(%ebx),%edx
    12ee:	89 50 04             	mov    %edx,0x4(%eax)
    12f1:	89 83 74 00 00 00    	mov    %eax,0x74(%ebx)
    12f7:	83 c4 08             	add    $0x8,%esp
    12fa:	5b                   	pop    %ebx
    12fb:	c3                   	ret    
    12fc:	8d 83 28 e1 ff ff    	lea    -0x1ed8(%ebx),%eax
    1302:	50                   	push   %eax
    1303:	6a 16                	push   $0x16
    1305:	8d 83 f4 e0 ff ff    	lea    -0x1f0c(%ebx),%eax
    130b:	50                   	push   %eax
    130c:	8d 83 fd e0 ff ff    	lea    -0x1f03(%ebx),%eax
    1312:	50                   	push   %eax
    1313:	e8 d8 fd ff ff       	call   10f0 <__assert_fail@plt>

00001318 <insert2>:
    1318:	53                   	push   %ebx
    1319:	83 ec 14             	sub    $0x14,%esp
    131c:	e8 1f fe ff ff       	call   1140 <__x86.get_pc_thunk.bx>
    1321:	81 c3 8b 2c 00 00    	add    $0x2c8b,%ebx
    1327:	6a 08                	push   $0x8
    1329:	e8 62 fd ff ff       	call   1090 <malloc@plt>
    132e:	83 c4 10             	add    $0x10,%esp
    1331:	85 c0                	test   %eax,%eax
    1333:	74 2f                	je     1364 <insert2+0x4c>
    1335:	8b 54 24 10          	mov    0x10(%esp),%edx
    1339:	89 10                	mov    %edx,(%eax)
    133b:	c7 40 04 00 00 00 00 	movl   $0x0,0x4(%eax)
    1342:	8b 8b 74 00 00 00    	mov    0x74(%ebx),%ecx
    1348:	85 c9                	test   %ecx,%ecx
    134a:	74 34                	je     1380 <insert2+0x68>
    134c:	8b 51 04             	mov    0x4(%ecx),%edx
    134f:	85 d2                	test   %edx,%edx
    1351:	74 09                	je     135c <insert2+0x44>
    1353:	89 d1                	mov    %edx,%ecx
    1355:	8b 52 04             	mov    0x4(%edx),%edx
    1358:	85 d2                	test   %edx,%edx
    135a:	75 f7                	jne    1353 <insert2+0x3b>
    135c:	89 41 04             	mov    %eax,0x4(%ecx)
    135f:	83 c4 08             	add    $0x8,%esp
    1362:	5b                   	pop    %ebx
    1363:	c3                   	ret    
    1364:	8d 83 20 e1 ff ff    	lea    -0x1ee0(%ebx),%eax
    136a:	50                   	push   %eax
    136b:	6a 1f                	push   $0x1f
    136d:	8d 83 f4 e0 ff ff    	lea    -0x1f0c(%ebx),%eax
    1373:	50                   	push   %eax
    1374:	8d 83 fd e0 ff ff    	lea    -0x1f03(%ebx),%eax
    137a:	50                   	push   %eax
    137b:	e8 70 fd ff ff       	call   10f0 <__assert_fail@plt>
    1380:	89 83 74 00 00 00    	mov    %eax,0x74(%ebx)
    1386:	eb d7                	jmp    135f <insert2+0x47>

00001388 <pop>:
    1388:	56                   	push   %esi
    1389:	53                   	push   %ebx
    138a:	83 ec 10             	sub    $0x10,%esp
    138d:	e8 ae fd ff ff       	call   1140 <__x86.get_pc_thunk.bx>
    1392:	81 c3 1a 2c 00 00    	add    $0x2c1a,%ebx
    1398:	8b 83 74 00 00 00    	mov    0x74(%ebx),%eax
    139e:	8b 50 04             	mov    0x4(%eax),%edx
    13a1:	89 93 74 00 00 00    	mov    %edx,0x74(%ebx)
    13a7:	8b 30                	mov    (%eax),%esi
    13a9:	50                   	push   %eax
    13aa:	e8 a1 fc ff ff       	call   1050 <free@plt>
    13af:	89 f0                	mov    %esi,%eax
    13b1:	83 c4 14             	add    $0x14,%esp
    13b4:	5b                   	pop    %ebx
    13b5:	5e                   	pop    %esi
    13b6:	c3                   	ret    

000013b7 <dump>:
    13b7:	57                   	push   %edi
    13b8:	56                   	push   %esi
    13b9:	53                   	push   %ebx
    13ba:	e8 81 fd ff ff       	call   1140 <__x86.get_pc_thunk.bx>
    13bf:	81 c3 ed 2b 00 00    	add    $0x2bed,%ebx
    13c5:	8b b3 74 00 00 00    	mov    0x74(%ebx),%esi
    13cb:	85 f6                	test   %esi,%esi
    13cd:	74 1d                	je     13ec <dump+0x35>
    13cf:	8d bb 07 e1 ff ff    	lea    -0x1ef9(%ebx),%edi
    13d5:	83 ec 04             	sub    $0x4,%esp
    13d8:	ff 36                	push   (%esi)
    13da:	57                   	push   %edi
    13db:	6a 01                	push   $0x1
    13dd:	e8 ee fc ff ff       	call   10d0 <__printf_chk@plt>
    13e2:	8b 76 04             	mov    0x4(%esi),%esi
    13e5:	83 c4 10             	add    $0x10,%esp
    13e8:	85 f6                	test   %esi,%esi
    13ea:	75 e9                	jne    13d5 <dump+0x1e>
    13ec:	5b                   	pop    %ebx
    13ed:	5e                   	pop    %esi
    13ee:	5f                   	pop    %edi
    13ef:	c3                   	ret    

000013f0 <main>:
    13f0:	8d 4c 24 04          	lea    0x4(%esp),%ecx
    13f4:	83 e4 f0             	and    $0xfffffff0,%esp
    13f7:	ff 71 fc             	push   -0x4(%ecx)
    13fa:	55                   	push   %ebp
    13fb:	89 e5                	mov    %esp,%ebp
    13fd:	57                   	push   %edi
    13fe:	56                   	push   %esi
    13ff:	53                   	push   %ebx
    1400:	51                   	push   %ecx
    1401:	81 ec 28 02 00 00    	sub    $0x228,%esp
    1407:	e8 34 fd ff ff       	call   1140 <__x86.get_pc_thunk.bx>
    140c:	81 c3 a0 2b 00 00    	add    $0x2ba0,%ebx
    1412:	8b 51 04             	mov    0x4(%ecx),%edx
    1415:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
    141b:	89 45 e4             	mov    %eax,-0x1c(%ebp)
    141e:	31 c0                	xor    %eax,%eax
    1420:	8b 83 48 00 00 00    	mov    0x48(%ebx),%eax
    1426:	8b 38                	mov    (%eax),%edi
    1428:	83 39 02             	cmpl   $0x2,(%ecx)
    142b:	74 6a                	je     1497 <main+0xa7>
    142d:	83 ec 0c             	sub    $0xc,%esp
    1430:	ff b3 64 00 00 00    	push   0x64(%ebx)
    1436:	e8 8a fe ff ff       	call   12c5 <insert1>
    143b:	83 c4 04             	add    $0x4,%esp
    143e:	ff b3 68 00 00 00    	push   0x68(%ebx)
    1444:	e8 cf fe ff ff       	call   1318 <insert2>
    1449:	83 c4 04             	add    $0x4,%esp
    144c:	ff b3 5c 00 00 00    	push   0x5c(%ebx)
    1452:	e8 6e fe ff ff       	call   12c5 <insert1>
    1457:	83 c4 04             	add    $0x4,%esp
    145a:	ff b3 6c 00 00 00    	push   0x6c(%ebx)
    1460:	e8 60 fe ff ff       	call   12c5 <insert1>
    1465:	83 c4 04             	add    $0x4,%esp
    1468:	ff b3 68 00 00 00    	push   0x68(%ebx)
    146e:	e8 52 fe ff ff       	call   12c5 <insert1>
    1473:	83 c4 04             	add    $0x4,%esp
    1476:	ff b3 60 00 00 00    	push   0x60(%ebx)
    147c:	e8 44 fe ff ff       	call   12c5 <insert1>
    1481:	83 c4 10             	add    $0x10,%esp
    1484:	be 01 00 00 00       	mov    $0x1,%esi
    1489:	8b 83 48 00 00 00    	mov    0x48(%ebx),%eax
    148f:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%ebp)
    1495:	eb 35                	jmp    14cc <main+0xdc>
    1497:	83 ec 08             	sub    $0x8,%esp
    149a:	8d 83 0b e1 ff ff    	lea    -0x1ef5(%ebx),%eax
    14a0:	50                   	push   %eax
    14a1:	ff 72 04             	push   0x4(%edx)
    14a4:	e8 17 fc ff ff       	call   10c0 <fopen@plt>
    14a9:	89 c7                	mov    %eax,%edi
    14ab:	83 c4 10             	add    $0x10,%esp
    14ae:	e9 7a ff ff ff       	jmp    142d <main+0x3d>
    14b3:	83 ec 04             	sub    $0x4,%esp
    14b6:	56                   	push   %esi
    14b7:	ff b5 d4 fd ff ff    	push   -0x22c(%ebp)
    14bd:	6a 01                	push   $0x1
    14bf:	e8 0c fc ff ff       	call   10d0 <__printf_chk@plt>
    14c4:	83 c4 10             	add    $0x10,%esp
    14c7:	eb 1e                	jmp    14e7 <main+0xf7>
    14c9:	83 c6 01             	add    $0x1,%esi
    14cc:	8d 83 0d e1 ff ff    	lea    -0x1ef3(%ebx),%eax
    14d2:	89 85 d4 fd ff ff    	mov    %eax,-0x22c(%ebp)
    14d8:	83 fe 06             	cmp    $0x6,%esi
    14db:	74 5b                	je     1538 <main+0x148>
    14dd:	8b 85 d0 fd ff ff    	mov    -0x230(%ebp),%eax
    14e3:	39 38                	cmp    %edi,(%eax)
    14e5:	74 cc                	je     14b3 <main+0xc3>
    14e7:	83 ec 04             	sub    $0x4,%esp
    14ea:	57                   	push   %edi
    14eb:	68 00 02 00 00       	push   $0x200
    14f0:	8d 85 e4 fd ff ff    	lea    -0x21c(%ebp),%eax
    14f6:	50                   	push   %eax
    14f7:	e8 64 fb ff ff       	call   1060 <fgets@plt>
    14fc:	83 c4 10             	add    $0x10,%esp
    14ff:	85 c0                	test   %eax,%eax
    1501:	74 d5                	je     14d8 <main+0xe8>
    1503:	83 ec 04             	sub    $0x4,%esp
    1506:	6a 0a                	push   $0xa
    1508:	6a 00                	push   $0x0
    150a:	8d 85 e4 fd ff ff    	lea    -0x21c(%ebp),%eax
    1510:	50                   	push   %eax
    1511:	e8 ca fb ff ff       	call   10e0 <strtol@plt>
    1516:	89 85 d4 fd ff ff    	mov    %eax,-0x22c(%ebp)
    151c:	e8 67 fe ff ff       	call   1388 <pop>
    1521:	89 c2                	mov    %eax,%edx
    1523:	8b 85 d4 fd ff ff    	mov    -0x22c(%ebp),%eax
    1529:	83 c0 02             	add    $0x2,%eax
    152c:	83 c4 10             	add    $0x10,%esp
    152f:	39 c2                	cmp    %eax,%edx
    1531:	74 96                	je     14c9 <main+0xd9>
    1533:	e8 05 fd ff ff       	call   123d <fail>
    1538:	e8 47 fd ff ff       	call   1284 <success>
    153d:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    1540:	65 2b 05 14 00 00 00 	sub    %gs:0x14,%eax
    1547:	75 11                	jne    155a <main+0x16a>
    1549:	b8 00 00 00 00       	mov    $0x0,%eax
    154e:	8d 65 f0             	lea    -0x10(%ebp),%esp
    1551:	59                   	pop    %ecx
    1552:	5b                   	pop    %ebx
    1553:	5e                   	pop    %esi
    1554:	5f                   	pop    %edi
    1555:	5d                   	pop    %ebp
    1556:	8d 61 fc             	lea    -0x4(%ecx),%esp
    1559:	c3                   	ret    
    155a:	e8 01 00 00 00       	call   1560 <__stack_chk_fail_local>
    155f:	90                   	nop

00001560 <__stack_chk_fail_local>:
    1560:	f3 0f 1e fb          	endbr32 
    1564:	53                   	push   %ebx
    1565:	e8 d6 fb ff ff       	call   1140 <__x86.get_pc_thunk.bx>
    156a:	81 c3 42 2a 00 00    	add    $0x2a42,%ebx
    1570:	83 ec 08             	sub    $0x8,%esp
    1573:	e8 08 fb ff ff       	call   1080 <__stack_chk_fail@plt>

Disassembly of section .fini:

00001578 <_fini>:
    1578:	f3 0f 1e fb          	endbr32 
    157c:	53                   	push   %ebx
    157d:	83 ec 08             	sub    $0x8,%esp
    1580:	e8 bb fb ff ff       	call   1140 <__x86.get_pc_thunk.bx>
    1585:	81 c3 27 2a 00 00    	add    $0x2a27,%ebx
    158b:	83 c4 08             	add    $0x8,%esp
    158e:	5b                   	pop    %ebx
    158f:	c3                   	ret    
