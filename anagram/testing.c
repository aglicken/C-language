
int getentry(int lastentry, int topic_num, topicentry * t)
{
	pthread_mutex_lock(&Topics[topic_num].lock);

	int data = -100; 

	if (is_empty(Topics[topic_num]) == 1)
	{
		data = -1;
		pthread_mutex_unlock(&Topics[topic_num].lock);
		return data;
	}

	int back_index = Topics[topic_num].back - 1;
	int back_num = Topics[topic_num].Queue[back_index].entrynum;

	int front_index = Topics[topic_num].front;
	int front_num = Topics[topic_num].Queue[front_index].entrynum;

 	printf("The entrynum needs to be between the front: index - %d num - %d and the back: index - %d num - %d\n", front_index, front_num, back_index, back_num);
	// for (int i = 0; i < Topics[topic_num].num_elements; i++)

	int i;
	for (i = front_num; i < Topics[topic_num].all_entries_num; i++)
	{
		if (Topics[topic_num].Queue[i].entrynum == lastentry)
		{
			*t = Topics[topic_num].Queue[i];
			pthread_mutex_unlock(&Topics[topic_num].lock);
			data = 1;
			printf("Here is your entry.\n");
			return data; //found
		}

		else if (Topics[topic_num].Queue[i].entrynum > lastentry)
		{
			*t = Topics[topic_num].Queue[i];
			int data = Topics[topic_num].Queue[i].entrynum;
			pthread_mutex_unlock(&Topics[topic_num].lock);
			printf("The item you were trying to read has been dequeued, the next available entry is #%d.\n", data);
			return data;
		}
	}
	if (data == -100)
	{
		printf("This is not a valid entry.\n");
		pthread_mutex_unlock(&Topics[topic_num].lock);
		return data;
	}

	Topics[topic_num].latest_getentry_num = data; // added
	// Topics[topic_num].last_read_entry = data;
	pthread_mutex_unlock(&Topics[topic_num].lock);
	// printf("Done with getentry\n");
	return data;
}

void * enqueue_the_topic(int topic_num, char URL[100], char CAPTION[100], int sleep_time)
{
	topicentry TQ;

	fprintf(stderr, "\tThis entry if for Topics[%d]\n", topic_num);

	TQ.entrynum = Topics[topic_num].all_entries_num;

	strcpy(TQ.photoUrl, URL);

	strcpy(TQ.photoCaption, CAPTION);

	gettimeofday(&TQ.timestamp, NULL);
	Enqueue(TQ, topic_num);
	sleep(sleep_time);

	return 0;
}

int sub(int topic_num, int lastentry)
{
	int found = 0;

	topicentry t;

	found = getentry(lastentry, topic_num, &t);

	if(found == -1)
	{
		// then the last entry has not been put into the queue yet bc the
		// queue is empty
		// lastentry stays the same
	}

	else if (found == 1)
	{
		// found the entry we were looking for
		lastentry++;
		Topics[topic_num].last_read_entry = lastentry;
	}

	else if (found == -100)
	{
		// this means that they were trying to read an entry that has not been enqueued yet (not valid)
	}

	else
	{
		// means that the one we wanted was dequeued so it is returning
		// the 
		lastentry = found; // start reading for the next spot
		Topics[topic_num].last_read_entry = lastentry;
	}
	printf("This is what sub is returning %d and it is being saved as the last read entry in the Topic as %d\n", Topics[topic_num].last_read_entry, lastentry );
	return lastentry;
}

void * fake_pub(void * name)
{
	while(EXIT_P == 0)
	{

	}
	fprintf(stderr, "Done with pub()\n");
	return 0;
}

void * fake_sub(void * name)
{
	while(EXIT_S == 0)
	{
		
	}
	fprintf(stderr, "Done with sub()\n");
	return 0;
}

void * publisher(void * file)
{
	while(EXIT_P == 0);

	FILE * publisher_file = (FILE *) file;
	topicentry TQ;

	int line_count = count_file_lines(publisher_file);
	char line[1024];

	int topic_num = 0;
	char URL[100];
	char CAPTION[100];
	int sleep;

	fseek(publisher_file, 0, SEEK_SET);

	while(line_count > 0)
	{
		TQ.entrynum = Topics[topic_num].all_entries_num;
    	// fprintf(stderr, "Entrynum: %d\n", TQ.entrynum);

		fgets(line, sizeof(line), publisher_file);
		sscanf(line, "%d", &topic_num);

		fgets(line, sizeof(line), publisher_file);
		// sscanf(line, "%s", URL);
		strcpy(TQ.photoUrl, line);

		fgets(line, sizeof(line), publisher_file);
		// sscanf(line, "%s", CAPTION);
		strcpy(TQ.photoCaption, line);
		// fprintf(stderr, "%s\n", TQ.photoCaption);

		fgets(line, sizeof(line), publisher_file);
		sscanf(line, "%d", &sleep);
		// sleep(sleep);
		// usleep(sleep * 1000000);

		gettimeofday(&TQ.timestamp, NULL);
		usleep(sleep * 1000000);
		Enqueue(TQ, topic_num);

		// fprintf(stderr, "Timestamp: %ld\n", TQ.timestamp.tv_sec);
		// fprintf(stderr, "\nFinished enqueing Topics[%d] #%d entry.\n", topic_num, TQ.entrynum);

		// fprintf(stderr, "\n\n");

		line_count -= 4;
	}
	fprintf(stderr, "Done with the Publisher() function.\n");
	// printf("PUB - %d %d %d %d %d %d\n", Topics[1].Queue[0].entrynum, Topics[1].Queue[1].entrynum, Topics[1].Queue[2].entrynum, Topics[1].Queue[3].entrynum, Topics[1].Queue[4].entrynum, Topics[1].Queue[5].entrynum);	
	return 0;
}

void * cleanup_thread(void * data) // start function
{
	while(EXIT_C == 0);

	int quit_cleanup = 1;
	int rt = 0;

	// while(quit_cleanup)
	while(EXIT_VAR == 0)
	{
		struct timeval time;
		gettimeofday(&time, NULL);

		int i, j, ii;
		for (i = 0; i <= maxtopics; i++)
		{
			int front_index = Topics[i].front;
			// printf("Front index - %d\n", front_index);

			int front_num = Topics[i].Queue[front_index].entrynum;
			// printf("Front num - %d\n", front_num);


			// for (j = Topics[i].front; j <= Topics[i].num_elements+1; j++)
			// printf("for %d <= %d - ++\n", Topics[i].front, Topics[i].all_entries_num);
			for (j = front_num; j < Topics[i].all_entries_num; j++)
    		{
    			// printf("-- INDEX: through %d -- for topic %d\n", j, i);
    			// ii = (j % maxentries);
				// printf("Checking this entry num: %d and ii with the mod is: %d\n", i, ii);
  				long age;
				age = labs(Topics[i].Queue[j].timestamp.tv_sec - time.tv_sec);
				// fprintf(stderr, "Trying to cleanup Topic # %d, Timestamp: %ld, Age: %ld for the Topic num of %d\n", i, Topics[i].Queue[j].timestamp.tv_sec, age, Topics[i].Queue[j].entrynum);
				
				if (age > DELTA)
				{
					// printf("trying to dequeue entry %d - url = %s\n", Topics[i].Queue[j].entrynum, Topics[i].Queue[j].photoUrl);
					Dequeue(i);
					// printf("\tEntry #%d has expired and been removed from Topic #%d\n\n", Topics[i].Queue[j].entrynum, i);
				}
				else
				{
					// printf("\tNot the time to dequeue, entry #%d has not expired yet.\n\n", Topics[i].Queue[j].entrynum);
				}
			}

			rt = check_if_all_empty();
			if (rt == 1)
			{
				// printf("Cleanup is done now. Everything is empty.\n\n");
				quit_cleanup = 0;
			}
		}
	}
	printf("Cleanup is done now. Everything is empty.\n\n");
	return 0;
}


void * subscriber(void * file)
{
	while(EXIT_S == 0)
	{
		// printf("Swait\t");
	}

	FILE * subscriber_file = (FILE *) file;
	topicentry TQ;

	int line_count = count_file_lines(subscriber_file);

	char line[1024];

	fseek(subscriber_file, 0, SEEK_SET);

	while(line_count > 0)
	{
		sleep(2);
		// fprintf(stderr, "In the while loop for Subscriber().\n");
		// get topic #
		int topic_num = 0;

		fgets(line, sizeof(line), subscriber_file);
		sscanf(line, "%d", &topic_num);

		// printf("This is the last read entry num BEFORE getting the entry - %d\n", Topics[topic_num].last_read_entry);
		sub(topic_num, Topics[topic_num].last_read_entry);
		// printf("This is the last read entry num - %d\n\n", Topics[topic_num].last_read_entry);

		line_count--;
	}
	fprintf(stderr, "Done with the Subscriber() function.\n\n");
	// EXIT_VAR++;
	return 0;
}

