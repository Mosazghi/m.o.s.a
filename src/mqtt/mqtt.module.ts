import { Module } from '@nestjs/common';
import { ClientsModule, Transport } from '@nestjs/microservices';
import { MqttController } from './mqtt.controller';

@Module({
  imports: [
    ClientsModule.register([
      {
        name: 'MQTT_CLIENT',
        transport: Transport.MQTT,
        options: {
          url: 'mqtt://mqtt_server_address:mqtt_port',
        },
      },
    ]),
  ],
  controllers: [MqttController],
})
export class MqttModule {}
