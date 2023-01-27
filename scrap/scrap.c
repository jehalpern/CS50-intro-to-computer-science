 sprintf(filename, "%03i.jpg", n);
                    FILE *img = fopen(filename, "w");
                    m = i;
                    p = m + 512;
                    for (int j = m; j < p; j++)
                    {
                        if ((ptr[j] & 0xf0) != 0xe0)
                        {
                            fwrite(ptr, sizeof(hex_size), 1, img);
                        }
                        else if ((ptr[j] & 0xf0) == 0xe0)
                        {
                            fwrite(ptr, sizeof(hex_size), 1, img);
                            fclose(img);
                            break;








while(fread(ptr, sizeof(hex_size), 512, data) == 512)
    {
        for (int i = 0; i < 512; i++)
            {
                if (n < 0)
                {
                    if (ptr[i] == 0xff && ptr[i + 1] == 0xd8 && ptr[i + 2] == 0xff)
                    {
                        n = n + 1;
                        if (n == 0)
                        {
                            sprintf(filename, "%03i.jpg", n);
                            FILE *img = fopen(filename, "w");
                            m = i;
                            p = 512 - i;
                            for (int j = m; j < p; j++)
                            {
                                if ((ptr[j] & 0xf0) != 0xe0)
                                {
                                    fwrite(ptr, sizeof(hex_size), 1, img);
                                }
                            }
                        }
                    }
                }

                else if (n >= 0)
                {
                    if (n == 0)
                    {
                        for (int j = m; j < p; j++)
                            {
                                if ((ptr[j] & 0xf0) != 0xe0)
                                {
                                    fwrite(ptr, sizeof(hex_size), 1, img);
                                }

                               else if ((ptr[j] & 0xf0) == 0xe0)
                                {
                                    fwrite(ptr, sizeof(hex_size), 1, img);
                                    fclose(img);
                                    break;
                                }
                            }
                    }
                }
            }

    }
    free(ptr);