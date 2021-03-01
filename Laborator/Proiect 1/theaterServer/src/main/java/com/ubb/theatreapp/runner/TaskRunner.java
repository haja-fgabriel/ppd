package com.ubb.theatreapp.runner;

import com.ubb.theatreapp.dto.SaleDto;
import com.ubb.theatreapp.service.SaleService;
import com.ubb.theatreapp.service.TheaterService;
import com.ubb.theatreapp.utils.Constants;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import java.util.Arrays;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

@Component("taskRunner")
public class TaskRunner {

    @Autowired
    private SaleService saleService;

    @Autowired
    private TheaterService theaterService;

    ExecutorService executor;
    private final static int NTHREADS = 8;

    public Builder builder(TaskType type) {
        return new Builder(type);
    }

    public class Builder {
        private TaskType type;
        private Object[] _args;

        private Builder(TaskType type) {
            this.type = type;
        }

        public Builder args(Object... args) {
            this._args = Arrays.copyOf(args, args.length);
            return this;
        }

        public Task build() {
            switch (type) {
                case ADD_SALE: return new AddSaleTask(saleService, (SaleDto) _args[0]);
                case DATA_VALIDATOR_START: return new DataValidatorStartTask(theaterService);
                case SHUTDOWN: return new ShutdownTask((long)_args[0]);
                default: return null;
            }
        }
    }

    @PostConstruct
    public void initialize() {
        executor = Executors.newFixedThreadPool(NTHREADS);
        addInitialTasks();
    }

    private void addInitialTasks() {
        addTask(builder(TaskType.DATA_VALIDATOR_START).build());
        addTask(builder(TaskType.SHUTDOWN).args(Constants.RUNNING_TIME).build());
    }

    public Future<Object> addTask(Task t) {
        return executor.submit(t);
    }

}
