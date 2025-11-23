#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// init WiFi + HTTP server
void wifi_hal_init(void);

// call often from loop
void wifi_hal_task(void);

#ifdef __cplusplus
}
#endif