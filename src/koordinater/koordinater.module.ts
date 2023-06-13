import { Module } from '@nestjs/common';
import { KoordinaterService } from './services/koordinater.service';
import { KoordinaterController } from './controllers/koordinater.controller';
import { MongooseModule } from '@nestjs/mongoose';
import { Koordinat, KoordinatSchema } from './schema/koordinat.schema';

@Module({
  imports: [
    MongooseModule.forFeature([{ name: 'koordinat', schema: KoordinatSchema }]),
  ],
  controllers: [KoordinaterController],
  providers: [KoordinaterService],
})
export class KoordinaterModule {}
