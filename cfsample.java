	public void sample1() throws Exception {
		CompletableFuture.supplyAsync(()->"x")
		 .thenApply(x->(char)1)                                // function return CF<Character>
		 .thenCompose(x->CompletableFuture.supplyAsync(()->1)) // CF<int>
		 .thenAccept(System.out::println)                      // accept consumer. CF<Void>
		 .thenRun(()->System.out.println("complete"));         // runnable CF<Void>
//		http://iteratrlearning.com/java9/2016/09/13/java9-timeouts-completablefutures.html
		CompletableFuture<Double> value = CompletableFuture.supplyAsync(()->{
				try { Thread.sleep(2000);}catch(Exception e) {}
					return "getPrice";
				}).thenCombine(CompletableFuture.supplyAsync(()->3.4), 
							(s,d)->{
								log.info("complete value");
								return d*(s.equals("getPrice")?2:3);});
			 
		// 1. blocking with timeout
		System.out.println("value:"+value.get(10, TimeUnit.SECONDS));
			
		// 2. with call back, but no timeout
		CompletableFuture<Void> cfv = value.thenAccept(
				v->System.out.println("result of cfv1:"+v));
		System.out.println("cf1 exceptional:"+cfv.isCompletedExceptionally());
			
		// 3. with call back and timeout, timeout won't run result
		CompletableFuture<Void> cfv2 = value.acceptEither(timeout(3,TimeUnit.SECONDS), 
				v->log.info("result of cfv2:"+v));
//		value.runAfterEither(other, action);
		log.info("cf2 exceptional:"+cfv2.isCompletedExceptionally());
	}
	public <T> CompletableFuture<T> timeout(long timeout, TimeUnit unit) {
	    CompletableFuture<T> result = new CompletableFuture<T>();
	    Executors.newScheduledThreadPool(1).schedule(() ->{
	    	log.info("schedule to complete exceptionally");
	    	result.completeExceptionally(new TimeoutException());}, timeout, unit);
	    return result;
	}
