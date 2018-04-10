	public static void times() {
		DateTimeFormatter ptn_int = DateTimeFormatter.ofPattern("yyyyMMddHHmmss");
		ZoneId local = ZoneId.systemDefault();
		ZoneId utc = ZoneId.of("UTC");
		LocalDateTime lcl_now = LocalDateTime.now();
		LocalDateTime parsed_local = LocalDateTime.parse("20180410050001", ptn_int);
		ZonedDateTime zd_now = ZonedDateTime.now();
		Instant instant1 = Instant.parse("2018-04-10T05:00:00.000Z");
		Instant instant2 = Instant.parse("2018-04-17T04:00:00.000Z");
		log.info(local+" "+ (local == ZoneId.of("America/New_York"))); // America/New_York true

		log.info(LocalDateTime.now().format(ptn_int)); // 20180410010000
		log.info(Instant.now()); // 2018-04-10T05:00:00.000Z   <-- in zulu
		
		// 2018-04-10T01:00:00.000  // empty, or default or America/New_York are the same
		log.info(lcl_now); 
		log.info(LocalDateTime.now(local));
        
		log.info(zd_now);                 // 2018-04-10T01:00:00.000-04:00[America/New_York]
		log.info(ZonedDateTime.now(utc)); // 2018-04-10T05:00:00.000Z[UTC]		
		ZonedDateTime.now().toLocalDateTime().atZone(local);
		// 2018-04-10T05:00:01Z[UTC]
		log.info(parsed_local.atZone(utc));
		// 2018-04-10T05:00:01-04:00[America/New_York]
		log.info(parsed_local.atZone(utc).withZoneSameLocal(local));

		// 2018-04-10T05:00:01
		log.info(parsed_local.atZone(utc).toLocalDateTime());
		// 2018-04-10T01:00:01  <- local at a zone then to a different zone then to local
		log.info(parsed_local.atZone(utc).withZoneSameInstant(local).toLocalDateTime());

		// 2018-04-10T05:00:01  <- same local, time not change unless invalid
		log.info(parsed_local.atZone(utc).toLocalDateTime());
		log.info(parsed_local.atZone(utc).withZoneSameLocal(local).toLocalDateTime());
		log.info(convert(parsed_local,null,local,utc, ptn_int));
		log.info(convert(parsed_local,null,utc,local, ptn_int));
		log.info(convert(null,null,utc,local, ptn_int));
		log.info(convert(null,null,local,utc, ptn_int));
//		log.info(Duration.between(instant1,instant2).toDays());  // 6 (6d23h)
//		LocalDate d = LocalDateTime.now().toLocalDate();
//		LocalTime t = LocalDateTime.now().toLocalTime();
//		LocalDate d1 = LocalDateTime.ofInstant(instant1, local).toLocalDate();
//		LocalDate d2 = LocalDateTime.ofInstant(instant2, local).toLocalDate();
//		log.info(Period.between(d1,d2).getDays()); // 7
	}
	// date_or_str: LocalDateTime or String
	// fmt1, fmt2: String or DateTimeFormatter
	// z1,z2: ZoneId, default Zone or String zone,
	public static String convert(Object date_or_str, Object fmt1, Object z1, Object z2, Object fmt2) {
		LocalDateTime date = 
				(fmt1 == null)?
				   date_or_str==null?LocalDateTime.now():(LocalDateTime)date_or_str// no parse needed
				  :LocalDateTime.parse((String)date_or_str, 
					   fmt1.getClass().equals("".getClass())?
							DateTimeFormatter.ofPattern((String)fmt1)
					       :(DateTimeFormatter)fmt1);
		LocalDateTime converted_local_date = 
		   date.atZone(z1==null? ZoneId.systemDefault()
			          :z1.getClass().equals(ZoneId.systemDefault().getClass())?(ZoneId)z1
			          :ZoneId.of((String)z1))
		       .withZoneSameInstant(z2==null? ZoneId.systemDefault()
			                       :z2.getClass().equals(ZoneId.systemDefault().getClass())?(ZoneId)z2
			                       :ZoneId.of((String)z2))
		       .toLocalDateTime();
		DateTimeFormatter ptn2 = fmt2.getClass().equals("".getClass())?
							  DateTimeFormatter.ofPattern((String)fmt2)
			                :(DateTimeFormatter)fmt2;
		return converted_local_date.format(ptn2);
	}

