import { Module } from '@nestjs/common';
import { MongooseModule } from '@nestjs/mongoose';
import { KomponentController } from './komponent.controller';
import { KomponentService } from './komponent.service';
import { Komponent, KomponentSchema } from './schema/komponent.schema';

@Module({
  imports: [
    MongooseModule.forFeature([
      { name: Komponent.name, schema: KomponentSchema },
    ]),
  ],
  controllers: [KomponentController],
  providers: [KomponentService],
})
export class KomponentModule {}
